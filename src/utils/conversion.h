#ifndef GREEDY_CONSTRUCTION_CONVERSION_H
#define GREEDY_CONSTRUCTION_CONVERSION_H

#include <cmath>

namespace conversion {

    const auto earthRadius = 6371.0;

    static double haversine(double lon1, double lat1, double lon2, double lat2) {
        auto degree2radian = [](double deg) {
            return deg * M_PI / 180.0;
        };

        lon1 = degree2radian(lon1);
        lat1 = degree2radian(lat1);
        lon2 = degree2radian(lon2);
        lat2 = degree2radian(lat2);

        auto diffLon = lon2 - lon1;
        auto diffLat = lat2 - lat1;
        auto a = std::pow(sin(diffLat / 2), 2) + cos(lat1) * cos(lat2) * std::pow(sin(diffLon / 2), 2);
        auto c = 2 * asin(sqrt(a));
        return c * earthRadius;
    }

} //conversion

#endif //GREEDY_CONSTRUCTION_CONVERSION_H
