#include <iostream>
#include <gtest/gtest.h>
#include "poly.h"


TEST (test_pol, positive_x) {
    int x = pol<1, 3, 2, 2, 1, 4, 0>::val;
    std::cout << x << std::endl;
    EXPECT_EQ(x, 9);
    x = pol<2, 100, 2, -20, 1, 4, 0>::val;
    std::cout << x << std::endl;
    EXPECT_EQ(x, 364);
    x = pol<122, 3, 2, 2, 1, 4, 0>::val;
    std::cout << x << std::endl;
    EXPECT_EQ(x, 44900);
}

TEST (test_pol, negative_x) {
    int x = pol<-1, 3, 2, 2, 1, 4, 0>::val;
    std::cout << x << std::endl;
    EXPECT_EQ(x, 5);
    x = pol<-2, 100, 2, -20, 1, 4, 0>::val;
    std::cout << x << std::endl;
    EXPECT_EQ(x, 444);
    x = pol<-122, 3, 3, 2, 1, 4, 0>::val;
    std::cout << x << std::endl;
    EXPECT_EQ(x, -5447784);
}




int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

