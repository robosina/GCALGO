#ifndef GREEDY_CONSTRUCTION_CUSTOMER_H
#define GREEDY_CONSTRUCTION_CUSTOMER_H

#include <cinttypes>

#include <string>

#include "pickup.h"

class customer {
public:
    std::string ID;
    double latitude;
    double longitude;
    std::string pickLocation;
};


#endif //GREEDY_CONSTRUCTION_CUSTOMER_H
