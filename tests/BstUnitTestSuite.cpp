#include "test_functions.hpp"
#include "BstUnitTestSuite.hpp"

void BstUnitTestSuite::SetUp() {
  values = GetRandomNumbers(size);
}

void BstUnitTestSuite::TearDown() {
  Test::TearDown();
}
