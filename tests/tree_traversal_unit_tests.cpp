#include <sstream>

#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

#include "test_functions.hpp"
#include "lib/tree/BinarySearchTree.hpp"
#include "lib/tree/InOrder.hpp"
#include "lib/tree/PreOrder.hpp"
#include "lib/tree/PostOrder.hpp"

using namespace bialger;

using IntTree = BinarySearchTree<int32_t, int32_t*, std::less<>, std::equal_to<>, std::allocator<int32_t>>;
using StringTree = BinarySearchTree<std::string,
                                    std::string*,
                                    std::less<>,
                                    std::equal_to<>,
                                    std::allocator<std::string>>;

TEST(TreeTraversalUnitTestSuite, InOrderTraverseTreeTest0) {
  std::vector<std::string> real_traverse;
  std::vector<std::string> class_traverse;
  StringTree bst{};
  InOrder in_order(bst);
  ITraversal& traversal = in_order;
  std::vector<std::string> values{"test", "test1", "t", "_", "", "r", "abcdef", "1"};

  for (std::string& value : values) {
    bst.Insert(value, &value);
  }

  bst.InOrder([&](StringTree::NodeType* node) -> void {
    real_traverse.push_back(node->key);
  });

  ITreeNode* begin = traversal.GetFirst();
  ITreeNode* end = bst.GetEnd();

  for (ITreeNode* it = begin; it != end; it = traversal.GetSuccessor(it)) {
    class_traverse.push_back(dynamic_cast<StringTree::NodeType*>(it)->key);
  }

  ASSERT_EQ(real_traverse, class_traverse);
}

TEST(TreeTraversalUnitTestSuite, InOrderMutableTraverseTreeTest1) {
  std::vector<int32_t> real_traverse;
  std::vector<int32_t> class_traverse;
  IntTree bst{};
  size_t size = 10000;
  std::vector<int32_t> values = GetRandomNumbers(size);
  InOrder in_order(bst);
  ITraversal& traversal = in_order;

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  bst.InOrder([&](IntTree::NodeType* node) -> void {
    real_traverse.push_back(node->key);
  });

  ITreeNode* begin = traversal.GetFirst();
  ITreeNode* end = bst.GetEnd();

  for (ITreeNode* it = begin; it != end; it = traversal.GetSuccessor(it)) {
    class_traverse.push_back(dynamic_cast<IntTree::NodeType*>(it)->key);
  }

  ASSERT_EQ(real_traverse, class_traverse);
}

TEST(TreeTraversalUnitTestSuite, InOrderMutableReversedTraverseTreeTest1) {
  std::vector<int32_t> real_traverse;
  std::vector<int32_t> class_traverse;
  IntTree bst{};
  size_t size = 10000;
  std::vector<int32_t> values = GetRandomNumbers(size);
  InOrder in_order(bst);
  ITraversal& traversal = in_order;

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  bst.InOrder([&](IntTree::NodeType* node) -> void {
    real_traverse.push_back(node->key);
  });

  ITreeNode* rbegin = traversal.GetLast();
  ITreeNode* rend = bst.GetEnd();

  for (ITreeNode* it = rbegin; it != rend; it = traversal.GetPredecessor(it)) {
    class_traverse.push_back(dynamic_cast<IntTree::NodeType*>(it)->key);
  }

  std::reverse(real_traverse.begin(), real_traverse.end());

  ASSERT_EQ(real_traverse, class_traverse);
}

TEST(TreeTraversalUnitTestSuite, PreOrderMutableTraverseTreeTest1) {
  std::vector<int32_t> real_traverse;
  std::vector<int32_t> class_traverse;
  IntTree bst{};
  size_t size = 10000;
  std::vector<int32_t> values = GetRandomNumbers(size);
  PreOrder pre_order(bst);
  ITraversal& traversal = pre_order;

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  bst.PreOrder([&](IntTree::NodeType* node) -> void {
    real_traverse.push_back(node->key);
  });

  ITreeNode* begin = traversal.GetFirst();
  ITreeNode* end = bst.GetEnd();

  for (ITreeNode* it = begin; it != end; it = traversal.GetSuccessor(it)) {
    class_traverse.push_back(dynamic_cast<IntTree::NodeType*>(it)->key);
  }

  ASSERT_EQ(real_traverse, class_traverse);
}

TEST(TreeTraversalUnitTestSuite, PreOrderMutableReversedTraverseTreeTest1) {
  std::vector<int32_t> real_traverse;
  std::vector<int32_t> class_traverse;
  IntTree bst{};
  size_t size = 10000;
  std::vector<int32_t> values = GetRandomNumbers(size);
  PreOrder pre_order(bst);
  ITraversal& traversal = pre_order;

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  bst.PreOrder([&](IntTree::NodeType* node) -> void {
    real_traverse.push_back(node->key);
  });

  ITreeNode* rbegin = traversal.GetLast();
  ITreeNode* rend = bst.GetEnd();

  for (ITreeNode* it = rbegin; it != rend; it = traversal.GetPredecessor(it)) {
    class_traverse.push_back(dynamic_cast<IntTree::NodeType*>(it)->key);
  }

  std::reverse(real_traverse.begin(), real_traverse.end());

  ASSERT_EQ(real_traverse, class_traverse);
}

TEST(TreeTraversalUnitTestSuite, PostOrderMutableTraverseTreeTest1) {
  std::vector<int32_t> real_traverse;
  std::vector<int32_t> class_traverse;
  IntTree bst{};
  size_t size = 10000;
  std::vector<int32_t> values = GetRandomNumbers(size);
  PostOrder post_order(bst);
  ITraversal& traversal = post_order;

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  bst.PostOrder([&](IntTree::NodeType* node) -> void {
    real_traverse.push_back(node->key);
  });

  ITreeNode* begin = traversal.GetFirst();
  ITreeNode* end = bst.GetEnd();

  for (ITreeNode* it = begin; it != end; it = traversal.GetSuccessor(it)) {
    class_traverse.push_back(dynamic_cast<IntTree::NodeType*>(it)->key);
  }

  ASSERT_EQ(real_traverse, class_traverse);
}

TEST(TreeTraversalUnitTestSuite, PostOrderMutableReversedTraverseTreeTest1) {
  std::vector<int32_t> real_traverse;
  std::vector<int32_t> class_traverse;
  IntTree bst{};
  size_t size = 10000;
  std::vector<int32_t> values = GetRandomNumbers(size);
  PostOrder post_order(bst);
  ITraversal& traversal = post_order;

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  bst.PostOrder([&](IntTree::NodeType* node) -> void {
    real_traverse.push_back(node->key);
  });

  ITreeNode* rbegin = traversal.GetLast();
  ITreeNode* rend = bst.GetEnd();

  for (ITreeNode* it = rbegin; it != rend; it = traversal.GetPredecessor(it)) {
    class_traverse.push_back(dynamic_cast<IntTree::NodeType*>(it)->key);
  }

  std::reverse(real_traverse.begin(), real_traverse.end());

  ASSERT_EQ(real_traverse, class_traverse);
}

TEST(TreeTraversalUnitTestSuite, InOrderFullTraverseTreeTest) {
  std::vector<int32_t> real_traverse;
  std::vector<int32_t> class_traverse;
  IntTree bst{};
  std::vector<int32_t> values = {50, 40, 30, 20, 10, 31, 39, 38, 37, 36, 45, 43,
                                 44, 42, 41, 47, 46, 48, 60, 70, 80, 90, 81, 82,
                                 83, 84, 85, 69, 68, 55, 57, 56, 58, 53, 52, 51};
  InOrder in_order(bst);
  ITraversal& traversal = in_order;

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  bst.InOrder([&](IntTree::NodeType* node) -> void {
    real_traverse.push_back(node->key);
  });

  ITreeNode* begin = traversal.GetFirst();
  ITreeNode* end = bst.GetEnd();

  for (ITreeNode* it = begin; it != end; it = traversal.GetSuccessor(it)) {
    class_traverse.push_back(dynamic_cast<IntTree::NodeType*>(it)->key);
  }

  ASSERT_EQ(real_traverse, class_traverse);
  real_traverse.clear();
  class_traverse.clear();

  bst.InOrder([&](IntTree::NodeType* node) -> void {
    real_traverse.push_back(node->key);
  });

  ITreeNode* rbegin = traversal.GetLast();
  ITreeNode* rend = bst.GetEnd();

  for (ITreeNode* it = rbegin; it != rend; it = traversal.GetPredecessor(it)) {
    class_traverse.push_back(dynamic_cast<IntTree::NodeType*>(it)->key);
  }

  std::reverse(real_traverse.begin(), real_traverse.end());

  ASSERT_EQ(real_traverse, class_traverse);
}

TEST(TreeTraversalUnitTestSuite, PreOrderFullTraverseTreeTest) {
  std::vector<int32_t> real_traverse;
  std::vector<int32_t> class_traverse;
  IntTree bst{};
  std::vector<int32_t> values = {50, 40, 30, 20, 10, 31, 39, 38, 37, 36, 45, 43,
                                 44, 42, 41, 47, 46, 48, 60, 70, 80, 90, 81, 82,
                                 83, 84, 85, 69, 68, 55, 57, 56, 58, 53, 52, 51};
  PreOrder pre_order(bst);
  ITraversal& traversal = pre_order;

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  bst.PreOrder([&](IntTree::NodeType* node) -> void {
    real_traverse.push_back(node->key);
  });

  ITreeNode* begin = traversal.GetFirst();
  ITreeNode* end = bst.GetEnd();

  for (ITreeNode* it = begin; it != end; it = traversal.GetSuccessor(it)) {
    class_traverse.push_back(dynamic_cast<IntTree::NodeType*>(it)->key);
  }

  ASSERT_EQ(real_traverse, class_traverse);
  real_traverse.clear();
  class_traverse.clear();

  bst.PreOrder([&](IntTree::NodeType* node) -> void {
    real_traverse.push_back(node->key);
  });

  ITreeNode* rbegin = traversal.GetLast();
  ITreeNode* rend = bst.GetEnd();

  for (ITreeNode* it = rbegin; it != rend; it = traversal.GetPredecessor(it)) {
    class_traverse.push_back(dynamic_cast<IntTree::NodeType*>(it)->key);
  }

  std::reverse(real_traverse.begin(), real_traverse.end());

  ASSERT_EQ(real_traverse, class_traverse);
}

TEST(TreeTraversalUnitTestSuite, PostOrderFullTraverseTreeTest) {
  std::vector<int32_t> real_traverse;
  std::vector<int32_t> class_traverse;
  IntTree bst{};
  std::vector<int32_t> values = {50, 40, 30, 20, 10, 31, 39, 38, 37, 36, 45, 43,
                                 44, 42, 41, 47, 46, 48, 60, 70, 80, 90, 81, 82,
                                 83, 84, 85, 69, 68, 55, 57, 56, 58, 53, 52, 51};
  PostOrder post_order(bst);
  ITraversal& traversal = post_order;

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  bst.PostOrder([&](IntTree::NodeType* node) -> void {
    real_traverse.push_back(node->key);
  });

  ITreeNode* begin = traversal.GetFirst();
  ITreeNode* end = bst.GetEnd();

  for (ITreeNode* it = begin; it != end; it = traversal.GetSuccessor(it)) {
    class_traverse.push_back(dynamic_cast<IntTree::NodeType*>(it)->key);
  }

  ASSERT_EQ(real_traverse, class_traverse);
  real_traverse.clear();
  class_traverse.clear();

  bst.PostOrder([&](IntTree::NodeType* node) -> void {
    real_traverse.push_back(node->key);
  });

  ITreeNode* rbegin = traversal.GetLast();
  ITreeNode* rend = bst.GetEnd();

  for (ITreeNode* it = rbegin; it != rend; it = traversal.GetPredecessor(it)) {
    class_traverse.push_back(dynamic_cast<IntTree::NodeType*>(it)->key);
  }

  std::reverse(real_traverse.begin(), real_traverse.end());

  ASSERT_EQ(real_traverse, class_traverse);
}
