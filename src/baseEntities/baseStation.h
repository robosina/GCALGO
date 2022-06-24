#ifndef GREEDY_CONSTRUCTION_BASESTATION_H
#define GREEDY_CONSTRUCTION_BASESTATION_H

#include <string>
#include <vector>
#include "utils/conversion.h"

/// This is the base class for entities with similar capabilities, such as customer and pickup.
struct baseStation {
    std::string PointId;
    double lat;
    double lng;
    std::string parentPointId;

    [[nodiscard]] double getDistanceInMeters(const baseStation &other) const {
        return conversion::haversine(this->lng, this->lat, other.lng, other.lat) * 1000; //1000 for converting km to m
    }
};

#endif //GREEDY_CONSTRUCTION_BASESTATION_H
