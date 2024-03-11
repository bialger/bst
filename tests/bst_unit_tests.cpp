#include <sstream>

#include "test_functions.hpp"
#include "BstUnitTestSuite.hpp"
#include <gtest/gtest.h>

TEST_F(BstUnitTestSuite, EmptyTest) {
  bialger::BST<int32_t> bst;
}