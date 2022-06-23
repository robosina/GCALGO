#ifndef GREEDY_CONSTRUCTION_PARSEJSONINFO_H
#define GREEDY_CONSTRUCTION_PARSEJSONINFO_H

#include <vector>

#include "customer.h"
#include "pickup.h"
#include "vehicle.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"

using customers_t = std::vector<customer>;
using pickups_t = std::vector<pickup>;
using vehicles_t = std::vector<vehicle>;
using location_t = std::pair<double,double>;

class parseJsonInfo {
public:
    void ParseInfo(const char *filePath);

    [[nodiscard]] const customers_t &customers() const;

    [[nodiscard]] const pickups_t &pickups() const;

    [[nodiscard]] const vehicles_t &vehicles() const;

    [[nodiscard]] const location_t &startLocation() const;

private:
    customers_t m_customers;
    pickups_t m_pickups;
    vehicles_t m_vehicles;
    location_t m_startLocation;

    rapidjson::Document readJsonFile(const char *filePath);

    void parseCustomersAndPickups(const rapidjson::Document &document);

    void parseStartLocation(const rapidjson::Document& document);

    void parseDrivers(const rapidjson::Document& document);

    void resetAllSets();
};


#endif //GREEDY_CONSTRUCTION_PARSEJSONINFO_H
