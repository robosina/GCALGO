#ifndef GREEDY_CONSTRUCTION_ROUTES_H
#define GREEDY_CONSTRUCTION_ROUTES_H

#include <string>
#include <vector>

#include "utils/conversion.h"

struct eachStation {
    std::string PointId;
    double lat;
    double lng;
    std::string parentPointId;

    [[nodiscard]] double getDistanceInMeters(const eachStation &other) const{
        return conversion::haversine(this->lng, this->lat, other.lng, other.lat) * 1000;
    }
};

using trip_t = std::vector<eachStation>;
using trips_t = std::vector<std::pair<trip_t, int>>; //trip_t and the total "distanceInMeter"

class routes {
    trips_t m_allRoutes;
public:
    void addNewTrip(const trip_t &trip);

    int getDistanceForATrip(const trip_t & trip);

    trips_t getTrips();
};


#endif //GREEDY_CONSTRUCTION_ROUTES_H
