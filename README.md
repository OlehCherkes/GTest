# GTest
unit tests
# About
![promo](/doc/promo.png)

## Google Test (GTest) installation on macOS
  - /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
  - brew install googletest

## Building a project for macOS
  - g++ -std=c++17 gtest.cpp -lgtest -lgtest_main -pthread -o gtest
  - ./gtest

For building 10 times
  - ./gtest --gtest_repeat=10
#
 - EXPECT_EQ(val1, val2), checks val1 and val2 for equality **val1 == val2** (test stops)
 - ASSERT_EQ(val1, val2), checks val1 and val2 for equality **val1 == val2** (test continue)
 - EXPECT_NE(val1, val2), checks val1 and val2 for not equals **val1 == val2** (test stops)
 - ASSERT_EQ(val1, val2), checks val1 and val2 for not equals **val1 == val2** (test continue)
 - EXPECT_GT(val1, val2), check that the value is greater than the specified range **val1 > val2**
 - EXPECT_GT(val1, val2), check that the value is greater than or equal to the specified range **val1 >= val2**
 - EXPECT_LT(val1, val2), check that the value is within or less than to the specified range **val1 < val2**
 - EXPECT_LE(val1, val2), check that the value is within or less than or equal to the specified range **val1 <= val2**
 - ASSERT_TRUE(val1 == val2), check the truth of the condition **TRUE**
 - ASSERT_FALSE(val1 == val2), check the truth of the condition **FALSE**

