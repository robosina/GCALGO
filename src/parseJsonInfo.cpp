#include <fstream>
#include "parseJsonInfo.h"

using namespace rapidjson;

void parseJsonInfo::ParseInfo(const char *filePath) {
    resetAllSets();
    auto document = readJsonFile(filePath);
    parseCustomersAndPickups(document);
    parseStartLocation(document);
    parseDrivers(document);
}

void parseJsonInfo::parseCustomersAndPickups(const rapidjson::Document &document) {
    for (auto &item: document["points"].GetArray()) {
        auto id = std::string(item["id"].GetString());
        auto lat = item["lat"].GetDouble();
        auto lng = item["lng"].GetDouble();
        auto parentId = std::string(item["parentPointId"].GetString());
        auto isOffloading = item["isOffloading"].GetBool();
        if (isOffloading) {
            m_customers.push_back({id, lat, lng, parentId});
        } else {
            m_pickups.push_back({id, lat, lng, 0.0}); //todo:pickLocation?
        }
    }
}

void parseJsonInfo::parseStartLocation(const Document &document) {
    auto startLocationObj = document["startLocation"].GetObject();
    m_startLocation = {startLocationObj["Lat"].GetDouble(), startLocationObj["Lng"].GetDouble()};
}

void parseJsonInfo::parseDrivers(const Document &document) {
    for (auto &item: document["vehicles"].GetArray()) {
        auto type = std::string(item["Type"].GetString());
        auto number = item["Number"].GetInt();
        for (int i = 0; i < number; i++) {
            m_vehicles.push_back({type, m_startLocation.first, m_startLocation.second});
        }
    }
}

void parseJsonInfo::resetAllSets() {
    m_customers.clear();
    m_pickups.clear();
    m_vehicles.clear();
}

const customers_t &parseJsonInfo::customers() const {
    return m_customers;
}

const pickups_t &parseJsonInfo::pickups() const {
    return m_pickups;
}

const vehicles_t &parseJsonInfo::vehicles() const {
    return m_vehicles;
}

const location_t &parseJsonInfo::startLocation() const {
    return m_startLocation;
}

rapidjson::Document parseJsonInfo::readJsonFile(const char *filePath) {
    using namespace rapidjson;

    std::ifstream ifs(filePath);
    IStreamWrapper isw(ifs);

    Document d;
    d.ParseStream(isw);
    return d;
}
