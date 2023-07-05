#include <gtest/gtest.h>

class Calculator {
public:
    int Add(int a, int b) {
        return a + b;
    }

    int Subtract(int a, int b) {
        return a - b;
    }
};

Calculator obj;

TEST(CalculatorTest, AddTest) {
    int result = obj.Add(3, 4);
    EXPECT_EQ(result, 7);   // Expected result 7
}

TEST(CalculatorTest, SubtractTest) {
    int result = obj.Subtract(7, 3);
    EXPECT_EQ(result, 4);  // Expected result 4
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}