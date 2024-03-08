#ifndef FORECASTUNITTESTSUITE_HPP_
#define FORECASTUNITTESTSUITE_HPP_

#include <filesystem>
#include <string>

#include <gtest/gtest.h>
#include "lib/tree/BinarySearchTree.hpp"
#include "lib/tree/InOrder.hpp"
#include "lib/tree/PreOrder.hpp"
#include "lib/tree/PostOrder.hpp"

struct TreeUnitTestSuite : public testing::Test { // special test structure
  const std::string kTemporaryDirectoryName = "./gtest_tree_tmp";
  const std::string kTemporaryFileName = kTemporaryDirectoryName + "/sample";

  void SetUp() override; // method that is called at the beginning of every test

  void TearDown() override; // method that is called at the end of every test
};

#endif //FORECASTUNITTESTSUITE_HPP_
