#include "test_functions.hpp"
#include "BstUnitTestSuite.hpp"

void BstUnitTestSuite::SetUp() {
  values = GetRandomNumbers(size);

  for (int32_t& value : values) {
    bst.insert(value);
  }
}

void BstUnitTestSuite::TearDown() {
  Test::TearDown();
}
