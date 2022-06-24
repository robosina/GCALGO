#ifndef GREEDY_CONSTRUCTION_ROUTES_H
#define GREEDY_CONSTRUCTION_ROUTES_H

#include "baseStation.h"


using trip_t = std::vector<baseStation>;
using trips_t = std::vector<std::pair<trip_t, int>>; //trip_t and the total "distanceInMeter"


class routes {
    trips_t m_allRoutes;
public:
    void addNewTrip(const trip_t &trip);

    /// each trip for a vehicle consist of multiple station(pickup and customers) so with this function
    /// we could calculate the total distance in meters
    /// \param trip
    /// \return total distance in meters
    static int getDistanceForATrip(const trip_t &trip);

    /// getter function for the trips(all vehicle trip)
    /// \return
    trips_t getTrips();
};


#endif //GREEDY_CONSTRUCTION_ROUTES_H
