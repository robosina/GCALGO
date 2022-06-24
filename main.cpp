#include <iostream>
#include <algorithm>

#include "parseJsonInfo.h"
#include "utils/conversion.h"
#include "routes.h"
#include "routesReport.h"

/// Find the nearest pickup from pickups to the vehicle
/// \param v vehicle
/// \param pickups
/// \param removeClosest remove the founded one or not
/// \return closest pickup
[[nodiscard]] pickup closestPickup(vehicle &v, pickups_t &pickups, bool removeClosest = false);

/// Find the nearest customer from customers to the vehicle
/// \param v vehicle
/// \param customers
/// \return closest customer
[[nodiscard]] customer closestCustomer(vehicle &v, customers_t &customers);

/// For each vehicle find the route
/// \param v
/// \param pickups
/// \param customers
/// \return set of stations
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
        auto d1 = conversion::haversine(v.lng, v.lat, p1.lng, p1.lat);
        auto d2 = conversion::haversine(v.lng, v.lat, p2.lng, p2.lat);
        return d1 < d2;
    });

    pickup bestPickUp = *it;
    v.lng = bestPickUp.lng;
    v.lat = bestPickUp.lat;
    if (removeClosest) pickups.erase(it);
    return bestPickUp;
}

customer closestCustomer(vehicle &v, customers_t &customers) {
    auto it = std::min_element(customers.begin(), customers.end(), [&](const customer &c1, const customer &c2) {
        auto d1 = conversion::haversine(v.lng, v.lat, c1.lng, c1.lat);
        auto d2 = conversion::haversine(v.lng, v.lat, c2.lng, c2.lat);
        return d1 < d2;
    });

    customer bestCustomer = *it;
    v.lng = bestCustomer.lng;
    v.lat = bestCustomer.lat;
    customers.erase(it);
    return bestCustomer;
}

trip_t findRouteForVehicle(vehicle &v, pickups_t &pickups, customers_t &customers) {
    trip_t newRoute;
    newRoute.push_back({"Start", v.lat, v.lng, ""});
    auto bestPickUp = closestPickup(v, pickups, true);
    newRoute.push_back({bestPickUp.PointId, bestPickUp.lat, bestPickUp.lng, ""});
    for (auto &c: customers) {
        if (c.parentPointId == bestPickUp.PointId) {
            auto bestCustomer = closestCustomer(v, customers);
            newRoute.push_back({bestCustomer.PointId, bestCustomer.lat, bestCustomer.lng, bestPickUp.PointId});
        }
    }
    return newRoute;
}