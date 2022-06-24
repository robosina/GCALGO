#include "routes.h"

void routes::addNewTrip(const trip_t &trip) {
    m_allRoutes.push_back({trip, getDistanceForATrip(trip)});
}

int routes::getDistanceForATrip(const trip_t &trip) {
    double s = 0;
    for (int i = 0; i < trip.size() - 1; i++) {
        s += trip[i].getDistanceInMeters(trip[i + 1]);
    }
    return static_cast<int>(s);
}

trips_t routes::getTrips() {
    return m_allRoutes;
}
