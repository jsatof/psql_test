#include <gtest/gtest.h>
#include <stub.h>

TEST(StubTestSuite, AlwaysPasses) {
    EXPECT_EQ(alwaysTrue(), true);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
