#ifndef BSTUNITTESTSUITE_HPP_
#define BSTUNITTESTSUITE_HPP_

#include <vector>
#include <sstream>
#include <random>
#include <limits>

#include <gtest/gtest.h>
#include "lib/bst/BST.hpp"

struct BstUnitTestSuite : public testing::Test { // special test structure
  void SetUp() override; // method that is called at the beginning of every test

  void TearDown() override; // method that is called at the end of every test

 protected:
  const size_t size = 1000;
  const size_t distance = 5;
  std::random_device dev;
  std::mt19937 rng{dev()};
  std::uniform_int_distribution<std::mt19937::result_type> dist{0, std::numeric_limits<uint32_t>::max()};
  std::vector<int32_t> values;
  std::vector<int32_t> values_unique;
  std::vector<int32_t> data_inorder;
  bialger::BST<int32_t> bst;
};

#endif //BSTUNITTESTSUITE_HPP_
