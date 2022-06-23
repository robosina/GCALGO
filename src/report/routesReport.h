#ifndef GREEDY_CONSTRUCTION_ROUTESREPORT_H
#define GREEDY_CONSTRUCTION_ROUTESREPORT_H


#include "routes.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include <rapidjson/stringbuffer.h>
#include <rapidjson/ostreamwrapper.h>
#include <fstream>
#include <iostream>

namespace report {

    inline static void generateReport(const trips_t &trips) {
        using namespace rapidjson;
        // document is the root of a json message
        rapidjson::Document document;

        document.SetObject();

        rapidjson::Value array(rapidjson::kArrayType);

        rapidjson::Document::AllocatorType &allocator = document.GetAllocator();

        rapidjson::Value rootArray(rapidjson::kArrayType);
        int counter = 1;
        for (const auto &item: trips) {
            auto trip = item.first;
            auto distance = item.second;
            rapidjson::Value EachTripInfo(rapidjson::kObjectType);
            auto countMessage = std::string("T") + std::to_string(counter);
            EachTripInfo.AddMember("tripId", rapidjson::Value(countMessage.c_str(), allocator), allocator);
            EachTripInfo.AddMember("vehicleType", "truck", allocator);
            rapidjson::Value summaryObject(rapidjson::kObjectType);
            rapidjson::Value tripArray(rapidjson::kArrayType);
            summaryObject.AddMember("distanceInMeter", distance, allocator);
            EachTripInfo.AddMember("summary", summaryObject, allocator);
            for (const auto &t: trip) {
                rapidjson::Value tripObject(rapidjson::kObjectType);
                tripObject.AddMember("pointId", rapidjson::Value(t.PointId.c_str(), allocator), allocator);
                tripObject.AddMember("lat", t.lat, allocator);
                tripObject.AddMember("lng", t.lng, allocator);
                tripObject.AddMember("parentPointId", rapidjson::Value(t.parentPointId.c_str(), allocator), allocator);
                tripArray.PushBack(tripObject, allocator);
            }
            EachTripInfo.AddMember("trip", tripArray, allocator);
            rootArray.PushBack(EachTripInfo, allocator);
            counter++;
        }

        document.AddMember("planID", "01", allocator);
        document.AddMember("trips", rootArray, allocator);

        std::ofstream ofs{"output.json"};
        if (!ofs.is_open()) {
            std::cerr << "Could not open file for writing!\n";
        }

        OStreamWrapper osw{ofs};
        PrettyWriter<OStreamWrapper> writer2{osw};
        document.Accept(writer2);
    }

} //report


#endif //GREEDY_CONSTRUCTION_ROUTESREPORT_H
