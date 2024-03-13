#ifndef BSTUNITTESTSUITE_HPP_
#define BSTUNITTESTSUITE_HPP_

#include <vector>
#include <sstream>

#include <gtest/gtest.h>
#include "lib/bst/BST.hpp"

struct BstUnitTestSuite : public testing::Test { // special test structure
  void SetUp() override; // method that is called at the beginning of every test

  void TearDown() override; // method that is called at the end of every test

 protected:
  const size_t size = 10000;
  std::vector<int32_t> values;
  std::vector<int32_t> data_inorder;
  bialger::BST<int32_t> bst;
};

#endif //BSTUNITTESTSUITE_HPP_
