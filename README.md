# GTest
unit tests

## Google Test (GTest) installation on macOS
  - /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
  - brew install googletest

## Building a project for macOS
  - g++ -std=c++17 gtest.cpp -lgtest -lgtest_main -pthread -o gtest
  - ./gtest


