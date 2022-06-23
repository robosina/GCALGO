#include <iostream>
#include <algorithm>

#include "parseJsonInfo.h"
#include "utils/conversion.h"
#include "routes.h"
#include "routesReport.h"

[[nodiscard]] pickup closestPickup(vehicle &v, pickups_t &pickups, bool removeClosest = false);

[[nodiscard]] customer closestCustomer(vehicle &v, customers_t &customers);

[[nodiscard]] trip_t findRouteForVehicle(vehicle &v, pickups_t &pickups, customers_t &customers);

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "usage ./greedy_construction path2json_file\n";
        return 0;
    }
    const char *filePath{argv[1]};

    parseJsonInfo pJInfo;
    pJInfo.ParseInfo(filePath);

    auto vehicles = pJInfo.vehicles();
    auto pickups = pJInfo.pickups();
    auto customers = pJInfo.customers();

    routes allRoutes;
    for (auto &vehicle: vehicles) {
        if (pickups.empty()) {
            break;
        }
        auto route = findRouteForVehicle(vehicle, pickups, customers);
        allRoutes.addNewTrip(route);
    }
    report::generateReport(allRoutes.getTrips());
}


pickup closestPickup(vehicle &v, pickups_t &pickups, bool removeClosest) {
    auto it = std::min_element(pickups.begin(), pickups.end(), [&](const pickup &p1, const pickup &p2) {
        auto d1 = conversion::haversine(v.longitude, v.latitude, p1.longitude, p1.latitude);
        auto d2 = conversion::haversine(v.longitude, v.latitude, p2.longitude, p2.latitude);
        return d1 < d2;
    });

    pickup bestPickUp = *it;
    v.longitude = bestPickUp.longitude;
    v.latitude = bestPickUp.latitude;
    if (removeClosest) pickups.erase(it);
    return bestPickUp;
}

customer closestCustomer(vehicle &v, customers_t &customers) {
    auto it = std::min_element(customers.begin(), customers.end(), [&](const customer &c1, const customer &c2) {
        auto d1 = conversion::haversine(v.longitude, v.latitude, c1.longitude, c1.latitude);
        auto d2 = conversion::haversine(v.longitude, v.latitude, c2.longitude, c2.latitude);
        return d1 < d2;
    });

    customer bestCustomer = *it;
    v.longitude = bestCustomer.longitude;
    v.latitude = bestCustomer.latitude;
    customers.erase(it);
    return bestCustomer;
}

trip_t findRouteForVehicle(vehicle &v, pickups_t &pickups, customers_t &customers) {
    trip_t newRoute;
    newRoute.push_back({"Start", v.latitude, v.longitude, ""});
    auto bestPickUp = closestPickup(v, pickups, true);
    newRoute.push_back({bestPickUp.ID, bestPickUp.latitude, bestPickUp.longitude, ""});
    for (auto &c: customers) {
        if (c.pickLocation == bestPickUp.ID) {
            auto bestCustomer = closestCustomer(v, customers);
            newRoute.push_back({bestCustomer.ID, bestCustomer.latitude, bestCustomer.longitude, bestPickUp.ID});
        }
    }
    return newRoute;
}