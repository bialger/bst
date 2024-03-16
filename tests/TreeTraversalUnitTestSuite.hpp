#ifndef TREETRAVERSALUNITTESTSUITE_HPP_
#define TREETRAVERSALUNITTESTSUITE_HPP_

#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "lib/tree/BinarySearchTree.hpp"
#include "lib/tree/InOrder.hpp"
#include "lib/tree/PreOrder.hpp"
#include "lib/tree/PostOrder.hpp"

using IntTree = bialger::BinarySearchTree<int32_t,
                                          int32_t*,
                                          std::less<>,
                                          bialger::Equivalent<void, std::less<>>,
                                          std::allocator<int32_t>>;

using StringTree = bialger::BinarySearchTree<std::string,
                                             std::string*,
                                             std::less<>,
                                             bialger::Equivalent<void, std::less<>>,
                                             std::allocator<std::string>>;

struct TreeTraversalUnitTestSuite : public testing::Test { // special test structure
  void SetUp() override; // method that is called at the beginning of every test

  void TearDown() override; // method that is called at the end of every test

 protected:
  std::vector<int32_t> real_traverse;
  std::vector<int32_t> class_traverse;
  IntTree bst;
  const size_t size = 10000;
  std::vector<int32_t> values;
  std::function<void(IntTree::NodeType * )> push_node;
};

#endif //TREETRAVERSALUNITTESTSUITE_HPP_
