#include <gtest/gtest.h>
#include "../src/utils/conversion.h"

TEST(TestConversion, haversine) {
    auto dist = conversion::haversine(-1.7297222222222221, 53.32055555555556, -1.6997222222222223, 53.31861111111111);
    EXPECT_TRUE(std::abs(dist - 2.00437) < 0.00001);
}