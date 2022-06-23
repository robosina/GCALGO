#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "src/parseJsonInfo.h"
#include "src/utils/conversion.h"

rapidjson::Document readJsonFile(const char *filePath);

struct eachStation {
    std::string PointId;
    double lat;
    double lng;
    std::string parentPointId;
};

using trip = std::vector<eachStation>;

[[nodiscard]] pickup getClosestPickup(vehicle &v, pickups_t &pickups, bool removeClosest = false) {
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

[[nodiscard]] customer
getClosestCustomer(vehicle &v, customers_t &customers) {
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

int main() {
    auto document = readJsonFile("/home/saeed/Downloads/raiese/greedy_construction/data/base.json");
    parseJsonInfo pJInfo;
    pJInfo.ParseInfo(document);

    auto vehicles = pJInfo.vehicles();
    auto pickups = pJInfo.pickups();
    auto customers = pJInfo.customers();
    for (auto &vehicle: vehicles) {
        if(pickups.empty()){
            break;
        }
        trip newRoute;
        newRoute.push_back({"Start", vehicle.latitude, vehicle.longitude, ""});
        auto bestPickUp = getClosestPickup(vehicle, pickups, true);
        newRoute.push_back({bestPickUp.ID, bestPickUp.latitude, bestPickUp.longitude, ""});
        for (auto &p: pickups) {
            auto bestPickUp = getClosestPickup(vehicle, pickups);
            newRoute.push_back({bestPickUp.ID, bestPickUp.latitude, bestPickUp.longitude, ""});
            for (auto &c: customers) {
                if(c.pickLocation==bestPickUp.ID){
                    auto bestCustomer = getClosestCustomer(vehicle,customers);
                    newRoute.push_back({bestCustomer.ID, bestCustomer.latitude, bestCustomer.longitude, ""});
                }
            }
        }
        int i = 0;
    }
}

rapidjson::Document readJsonFile(const char *filePath) {
    using namespace rapidjson;

    std::ifstream ifs(filePath);
    IStreamWrapper isw(ifs);

    Document d;
    d.ParseStream(isw);
    return d;
}