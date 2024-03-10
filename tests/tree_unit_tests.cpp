#include <sstream>

#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>
#include <random>

#include "test_functions.hpp"
#include "TreeUnitTestSuite.hpp"

using namespace bialger;

using IntTree = BinarySearchTree<int32_t, int32_t*, std::less<>, std::equal_to<>, std::allocator<int32_t>>;
using StringTree = BinarySearchTree<std::string, std::string*, std::less<>, std::equal_to<>, std::allocator<std::string>>;

TEST_F(TreeUnitTestSuite, EmptyTreeTest) {
  IntTree bst{};
}

TEST_F(TreeUnitTestSuite, InsertTreeTest1) {
  IntTree bst{};
  std::vector<int32_t> values{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }
}

TEST_F(TreeUnitTestSuite, InsertTreeTest2) {
  StringTree bst{};
  std::vector<std::string> values{"test", "test1", "t", "_", "", "r"};

  for (std::string& value : values) {
    bst.Insert(value, &value);
  }
}

TEST_F(TreeUnitTestSuite, InsertTreeTest3) {
  StringTree
      bst(true);
  std::vector<std::string> values{"test", "test1", "t", "test", "_", "", "r"};

  for (std::string& value : values) {
    bst.Insert(value, &value);
  }
}

TEST_F(TreeUnitTestSuite, InsertTreeTest4) {
  IntTree bst{};
  size_t size = 1000;
  std::vector<int32_t> values = GetRandomNumbers(size);

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }
}

TEST_F(TreeUnitTestSuite, CopyTreeTest1) {
  IntTree bst{};
  size_t size = 1000;
  std::vector<int32_t> values = GetRandomNumbers(size);

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  IntTree bst2 = bst;

  for (int32_t& value : values) {
    ASSERT_TRUE(bst.Contains(value));
    ASSERT_TRUE(bst2.Contains(value));
    ASSERT_NE(bst.FindFirst(value), bst2.FindFirst(value));
  }
}

TEST_F(TreeUnitTestSuite, CopyTreeTest2) {
  IntTree bst{};
  IntTree bst2{};
  size_t size = 1000;
  std::vector<int32_t> values = GetRandomNumbers(size);

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  bst2 = bst;

  for (int32_t& value : values) {
    ASSERT_TRUE(bst.Contains(value));
    ASSERT_TRUE(bst2.Contains(value));
    ASSERT_NE(bst.FindFirst(value), bst2.FindFirst(value));
  }
}

TEST_F(TreeUnitTestSuite, DeleteTreeTest1) {
  StringTree bst{};
  std::vector<std::string> values{"test", "test1", "t", "_", "", "r"};

  for (std::string& value : values) {
    bst.Insert(value, &value);
  }

  for (std::string& value : values) {
    bst.Delete(bst.FindFirst(value));
  }

  ASSERT_EQ(bst.GetRoot(), nullptr);
  ASSERT_EQ(bst.GetSize(), 0);
}

TEST_F(TreeUnitTestSuite, DeleteTreeTest2) {
  StringTree bst{};
  std::vector<std::string> values{"test", "test1", "t", "_", "", "r", "r", "abcdef", "1"};

  for (std::string& value : values) {
    bst.Insert(value, &value);
  }

  std::reverse(values.begin(), values.end());

  for (std::string& value : values) {
    bst.Delete(bst.FindFirst(value));
  }

  ASSERT_EQ(bst.GetRoot(), nullptr);
  ASSERT_EQ(bst.GetSize(), 0);
}

TEST_F(TreeUnitTestSuite, DeleteTreeTest3) {
  bialger::BinarySearchTree<int32_t, int32_t*, std::less<>, std::equal_to<>, std::allocator<int32_t>> bst{};
  std::vector<int32_t> values{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  std::reverse(values.begin(), values.end());

  for (int32_t& value : values) {
    bst.Delete(bst.FindFirst(value));
  }

  ASSERT_EQ(bst.GetRoot(), nullptr);
  ASSERT_EQ(bst.GetSize(), 0);
}

TEST_F(TreeUnitTestSuite, DeleteTreeTest4) {
  IntTree bst{};
  size_t size = 1000;
  std::vector<int32_t> values = GetRandomNumbers(size);

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  std::reverse(values.begin(), values.end());

  for (int32_t& value : values) {
    bst.Delete(bst.FindFirst(value));
  }

  ASSERT_EQ(bst.GetRoot(), nullptr);
  ASSERT_EQ(bst.GetSize(), 0);
}

TEST_F(TreeUnitTestSuite, DeleteTreeTest5) {
  IntTree bst{};
  size_t size = 10000;
  std::vector<int32_t> values = GetRandomNumbers(size);
  std::random_device dev;
  std::mt19937 rng(dev());

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  std::shuffle(values.begin(), values.end(), rng);

  for (int32_t& value : values) {
    bst.Delete(bst.FindFirst(value));
  }

  ASSERT_EQ(bst.GetRoot(), nullptr);
  ASSERT_EQ(bst.GetSize(), 0);
}

TEST_F(TreeUnitTestSuite, DeleteTreeTest6) {
  IntTree bst(true);
  size_t size = 1000;
  std::vector<int32_t> values_tmp = GetRandomNumbers(size);
  std::vector<int32_t> values(values_tmp);
  values.insert(values.end(), values_tmp.begin(), values_tmp.end());
  std::random_device dev;
  std::mt19937 rng(dev());
  std::shuffle(values.begin(), values.end(), rng);

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  std::shuffle(values.begin(), values.end(), rng);

  for (int32_t& value : values) {
    bst.Delete(bst.FindFirst(value));
  }

  ASSERT_EQ(bst.GetRoot(), nullptr);
  ASSERT_EQ(bst.GetSize(), 0);
}

TEST_F(TreeUnitTestSuite, InOrderTraverseTreeTest1) {
  std::vector<std::string> real_traverse;
  std::vector<std::string> class_traverse;
  StringTree bst{};
  InOrder in_order(bst);
  ITraversal& traversal = in_order;
  std::vector<std::string> values{"test", "test1", "t", "_", "", "r", "abcdef", "1"};

  for (std::string& value : values) {
    bst.Insert(value, &value);
  }

  bst.InOrder([&](const bialger::ITreeNode* node) -> void {
    real_traverse.push_back(dynamic_cast<const StringTree::NodeType*>(node)->key);
  });

  const ITreeNode* begin = traversal.GetFirst();
  const ITreeNode* end = bst.GetEnd();

  for (const ITreeNode* it = begin; it != end; it = traversal.GetSuccessor(it)) {
    class_traverse.push_back(dynamic_cast<const StringTree::NodeType*>(it)->key);
  }

  ASSERT_EQ(real_traverse, class_traverse);
}

TEST_F(TreeUnitTestSuite, InOrderTraverseTreeTest2) {
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

  bst.InOrder([&](const bialger::ITreeNode* node) -> void {
    real_traverse.push_back(dynamic_cast<const IntTree::NodeType*>(node)->key);
  });

  const ITreeNode* begin = traversal.GetFirst();
  const ITreeNode* end = bst.GetEnd();

  for (const ITreeNode* it = begin; it != end; it = traversal.GetSuccessor(it)) {
    class_traverse.push_back(dynamic_cast<const IntTree::NodeType*>(it)->key);
  }

  ASSERT_EQ(real_traverse, class_traverse);
}

TEST_F(TreeUnitTestSuite, InOrderReversedTraverseTreeTest1) {
  std::vector<int32_t> real_traverse;
  std::vector<int32_t> class_traverse;
  IntTree bst{};
  size_t size = 1000;
  std::vector<int32_t> values = GetRandomNumbers(size);
  InOrder in_order(bst);
  ITraversal& traversal = in_order;

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  bst.InOrder([&](const bialger::ITreeNode* node) -> void {
    real_traverse.push_back(dynamic_cast<const IntTree::NodeType*>(node)->key);
  });

  const ITreeNode* rbegin = traversal.GetLast();
  const ITreeNode* rend = bst.GetEnd();

  for (const ITreeNode* it = rbegin; it != rend; it = traversal.GetPredecessor(it)) {
    class_traverse.push_back(dynamic_cast<const IntTree::NodeType*>(it)->key);
  }

  std::reverse(real_traverse.begin(), real_traverse.end());

  ASSERT_EQ(real_traverse, class_traverse);
}

TEST_F(TreeUnitTestSuite, PreOrderTraverseTreeTest1) {
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

  bst.PreOrder([&](const bialger::ITreeNode* node) -> void {
    real_traverse.push_back(dynamic_cast<const IntTree::NodeType*>(node)->key);
  });

  const ITreeNode* begin = traversal.GetFirst();
  const ITreeNode* end = bst.GetEnd();

  for (const ITreeNode* it = begin; it != end; it = traversal.GetSuccessor(it)) {
    class_traverse.push_back(dynamic_cast<const IntTree::NodeType*>(it)->key);
  }

  ASSERT_EQ(real_traverse, class_traverse);
}

TEST_F(TreeUnitTestSuite, PreOrderReversedTraverseTreeTest1) {
  std::vector<int32_t> real_traverse;
  std::vector<int32_t> class_traverse;
  IntTree bst{};
  size_t size = 1000;
  std::vector<int32_t> values = GetRandomNumbers(size);
  PreOrder pre_order(bst);
  ITraversal& traversal = pre_order;

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  bst.PreOrder([&](const bialger::ITreeNode* node) -> void {
    real_traverse.push_back(dynamic_cast<const IntTree::NodeType*>(node)->key);
  });

  const ITreeNode* rbegin = traversal.GetLast();
  const ITreeNode* rend = bst.GetEnd();

  for (const ITreeNode* it = rbegin; it != rend; it = traversal.GetPredecessor(it)) {
    class_traverse.push_back(dynamic_cast<const IntTree::NodeType*>(it)->key);
  }

  std::reverse(real_traverse.begin(), real_traverse.end());

  ASSERT_EQ(real_traverse, class_traverse);
}

TEST_F(TreeUnitTestSuite, PostOrderTraverseTreeTest1) {
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

  bst.PostOrder([&](const bialger::ITreeNode* node) -> void {
    real_traverse.push_back(dynamic_cast<const IntTree::NodeType*>(node)->key);
  });

  const ITreeNode* begin = traversal.GetFirst();
  const ITreeNode* end = bst.GetEnd();

  for (const ITreeNode* it = begin; it != end; it = traversal.GetSuccessor(it)) {
    class_traverse.push_back(dynamic_cast<const IntTree::NodeType*>(it)->key);
  }

  ASSERT_EQ(real_traverse, class_traverse);
}

TEST_F(TreeUnitTestSuite, PostOrderReversedTraverseTreeTest1) {
  std::vector<int32_t> real_traverse;
  std::vector<int32_t> class_traverse;
  IntTree bst{};
  size_t size = 1000;
  std::vector<int32_t> values = GetRandomNumbers(size);
  PostOrder post_order(bst);
  ITraversal& traversal = post_order;

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  bst.PostOrder([&](const bialger::ITreeNode* node) -> void {
    real_traverse.push_back(dynamic_cast<const IntTree::NodeType*>(node)->key);
  });

  const ITreeNode* rbegin = traversal.GetLast();
  const ITreeNode* rend = bst.GetEnd();

  for (const ITreeNode* it = rbegin; it != rend; it = traversal.GetPredecessor(it)) {
    class_traverse.push_back(dynamic_cast<const IntTree::NodeType*>(it)->key);
  }

  std::reverse(real_traverse.begin(), real_traverse.end());

  ASSERT_EQ(real_traverse, class_traverse);
}
