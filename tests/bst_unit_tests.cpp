#include <sstream>

#include "test_functions.hpp"
#include "BstUnitTestSuite.hpp"

#include <vector>
#include <set>
#include <gtest/gtest.h>

using namespace bialger;

TEST_F(BstUnitTestSuite, IsIteratorTest1) {
  ASSERT_TRUE(is_iterator<std::vector<int32_t>::iterator>::value);
  ASSERT_TRUE(is_iterator<std::vector<int32_t>::const_iterator>::value);
  ASSERT_TRUE(is_iterator<std::set<int32_t>::iterator>::value);
  ASSERT_TRUE(is_iterator<std::set<int32_t>::const_iterator>::value);
}

TEST_F(BstUnitTestSuite, IsIteratorTest2) {
  ASSERT_FALSE(is_iterator<std::vector<int32_t>>::value);
  ASSERT_FALSE(is_iterator<int32_t>::value);
  ASSERT_FALSE(is_iterator<std::set<int32_t>>::value);
  ASSERT_FALSE(is_iterator<std::string>::value);
}

TEST_F(BstUnitTestSuite, IsIteratorTest3) {
  ASSERT_TRUE(is_iterator<BST<int32_t>::iterator>::value);
  ASSERT_TRUE(is_iterator<BST<int32_t>::const_iterator>::value);
  ASSERT_TRUE(is_iterator<BST<int32_t>::reverse_iterator>::value);
  ASSERT_TRUE(is_iterator<BST<int32_t>::const_reverse_iterator>::value);
}

TEST_F(BstUnitTestSuite, IsIterableTest1) {
  ASSERT_TRUE(is_iterable<std::vector<int32_t>>::value);
  ASSERT_TRUE(is_iterable<std::set<std::string>>::value);
  ASSERT_TRUE(is_iterable<std::string>::value);
}

TEST_F(BstUnitTestSuite, IsIterableTest2) {
  ASSERT_FALSE(is_iterable<std::vector<int32_t>::iterator>::value);
  ASSERT_FALSE(is_iterable<int32_t>::value);
  ASSERT_FALSE(is_iterable<std::set<int32_t>::iterator>::value);
}

TEST_F(BstUnitTestSuite, IsIterableTest3) {
  ASSERT_TRUE(is_iterable<BST<int32_t>>::value);
  ASSERT_TRUE(is_iterable<BST<std::string>>::value);
}

TEST_F(BstUnitTestSuite, EmptyTest) {
  BST<int32_t> bst;
  ASSERT_EQ(bst, bst);
}

TEST_F(BstUnitTestSuite, InsertTest1) {
  BST<int32_t> bst;
  std::vector<int32_t> values = {1, 2, 3, 4, 5};
  std::vector<int32_t> data_inorder;
  bst.insert(1);
  bst.insert(2);
  bst.insert(3);
  bst.insert(4);
  bst.insert(5);

  ASSERT_EQ(bst.size(), 5);

  for (const int32_t& val : bst) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(values, data_inorder);
}

TEST_F(BstUnitTestSuite, InOrderTraverseTreeTest1) {
  std::ostringstream real_traversal;
  std::ostringstream iterator_traversal;
  BST<int32_t> bst{};
  size_t size = 10000;
  std::vector<int32_t> values = GetRandomNumbers(size);

  for (int32_t& value : values) {
    bst.insert(value);
  }

  PrintToStream<int32_t>(bst, real_traversal);

  for (auto it = bst.begin(); it != bst.end(); ++it) {
    iterator_traversal << *it << ' ';
  }

  ASSERT_EQ(real_traversal.str(), iterator_traversal.str());
}

TEST_F(BstUnitTestSuite, InOrderReversedTraverseTreeTest1) {
  std::ostringstream real_traversal;
  std::ostringstream iterator_traversal;
  std::string reversed_real_traversal;
  BST<int32_t> bst{};
  size_t size = 10000;
  std::vector<int32_t> values = GetRandomNumbers(size);

  for (int32_t& value : values) {
    bst.insert(value);
  }

  PrintToStream<int32_t>(bst, real_traversal);
  std::vector<std::string> reversed_vector = SplitString(real_traversal.str());
  std::reverse(reversed_vector.begin(), reversed_vector.end());

  for (const std::string& value : reversed_vector) {
    reversed_real_traversal += value + " ";
  }

  for (auto it = bst.rbegin(); it != bst.rend(); ++it) {
    iterator_traversal << *it << ' ';
  }

  ASSERT_EQ(reversed_real_traversal, iterator_traversal.str());
}

TEST_F(BstUnitTestSuite, InOrderTraverseTreeBothWaysTest1) {
  std::ostringstream reversed_traversal;
  std::ostringstream iterator_traversal;
  BST<int32_t> bst{};
  size_t size = 10000;
  std::vector<int32_t> values = GetRandomNumbers(size);

  for (int32_t& value : values) {
    bst.insert(value);
  }

  for (auto it = bst.rbegin(); it != bst.rend(); ++it) {
    reversed_traversal << *it << ' ';
  }

  for (auto it = --bst.end(); it != bst.end(); --it) {
    iterator_traversal << *it << ' ';
  }

  ASSERT_EQ(reversed_traversal.str(), iterator_traversal.str());
}

TEST_F(BstUnitTestSuite, InOrderFirstAndLastTraverseTreeTest1) {
  std::ostringstream real_traversal;
  std::ostringstream iterator_traversal;
  BST<int32_t> bst{};
  size_t size = 10000;
  std::vector<int32_t> values = GetRandomNumbers(size);

  for (int32_t& value : values) {
    bst.insert(value);
  }

  auto it = bst.end();
  auto reverse_it = bst.rend();

  ASSERT_EQ(*--it, *bst.rbegin());
  ASSERT_EQ(*--reverse_it, *bst.begin());
}

TEST_F(BstUnitTestSuite, PreOrderTraverseTreeTest1) {
  std::ostringstream real_traversal;
  std::ostringstream iterator_traversal;
  BST<int32_t> bst{};
  size_t size = 10000;
  std::vector<int32_t> values = GetRandomNumbers(size);

  for (int32_t& value : values) {
    bst.insert(value);
  }

  PrintToStream<int32_t, PreOrder>(bst, real_traversal);

  for (auto it = bst.begin<PreOrder>(); it != bst.end<PreOrder>(); ++it) {
    iterator_traversal << *it << ' ';
  }

  ASSERT_EQ(real_traversal.str(), iterator_traversal.str());
}

TEST_F(BstUnitTestSuite, PreOrderReversedTraverseTreeTest1) {
  std::ostringstream real_traversal;
  std::ostringstream iterator_traversal;
  std::string reversed_real_traversal;
  BST<int32_t> bst{};
  size_t size = 10000;
  std::vector<int32_t> values = GetRandomNumbers(size);

  for (int32_t& value : values) {
    bst.insert(value);
  }

  PrintToStream<int32_t, PreOrder>(bst, real_traversal);
  std::vector<std::string> reversed_vector = SplitString(real_traversal.str());
  std::reverse(reversed_vector.begin(), reversed_vector.end());

  for (const std::string& value : reversed_vector) {
    reversed_real_traversal += value + " ";
  }

  for (auto it = bst.rbegin<PreOrder>(); it != bst.rend<PreOrder>(); ++it) {
    iterator_traversal << *it << ' ';
  }

  ASSERT_EQ(reversed_real_traversal, iterator_traversal.str());
}

TEST_F(BstUnitTestSuite, PreOrderFirstAndLastTraverseTreeTest1) {
  std::ostringstream real_traversal;
  std::ostringstream iterator_traversal;
  BST<int32_t> bst{};
  size_t size = 10000;
  std::vector<int32_t> values = GetRandomNumbers(size);

  for (int32_t& value : values) {
    bst.insert(value);
  }

  auto it = bst.end<PreOrder>();
  auto reverse_it = bst.rend<PreOrder>();

  ASSERT_EQ(*--it, *bst.rbegin<PreOrder>());
  ASSERT_EQ(*--reverse_it, *bst.begin<PreOrder>());
}

TEST_F(BstUnitTestSuite, PreOrderTraverseTreeBothWaysTest1) {
  std::ostringstream reversed_traversal;
  std::ostringstream iterator_traversal;
  BST<int32_t> bst{};
  size_t size = 10000;
  std::vector<int32_t> values = GetRandomNumbers(size);

  for (int32_t& value : values) {
    bst.insert(value);
  }

  for (auto it = bst.rbegin<PreOrder>(); it != bst.rend<PreOrder>(); ++it) {
    reversed_traversal << *it << ' ';
  }

  for (auto it = --bst.end<PreOrder>(); it != bst.end<PreOrder>(); --it) {
    iterator_traversal << *it << ' ';
  }

  ASSERT_EQ(reversed_traversal.str(), iterator_traversal.str());
}

TEST_F(BstUnitTestSuite, PostOrderTraverseTreeTest1) {
  std::ostringstream real_traversal;
  std::ostringstream iterator_traversal;
  BST<int32_t> bst{};
  size_t size = 10000;
  std::vector<int32_t> values = GetRandomNumbers(size);

  for (int32_t& value : values) {
    bst.insert(value);
  }

  PrintToStream<int32_t, PostOrder>(bst, real_traversal);

  for (auto it = bst.begin<PostOrder>(); it != bst.end<PostOrder>(); ++it) {
    iterator_traversal << *it << ' ';
  }

  ASSERT_EQ(real_traversal.str(), iterator_traversal.str());
}

TEST_F(BstUnitTestSuite, PostOrderReversedTraverseTreeTest1) {
  std::ostringstream real_traversal;
  std::ostringstream iterator_traversal;
  std::string reversed_real_traversal;
  BST<int32_t> bst{};
  size_t size = 10000;
  std::vector<int32_t> values = GetRandomNumbers(size);

  for (int32_t& value : values) {
    bst.insert(value);
  }

  PrintToStream<int32_t, PostOrder>(bst, real_traversal);
  std::vector<std::string> reversed_vector = SplitString(real_traversal.str());
  std::reverse(reversed_vector.begin(), reversed_vector.end());

  for (const std::string& value : reversed_vector) {
    reversed_real_traversal += value + " ";
  }

  for (auto it = bst.rbegin<PostOrder>(); it != bst.rend<PostOrder>(); ++it) {
    iterator_traversal << *it << ' ';
  }

  ASSERT_EQ(reversed_real_traversal, iterator_traversal.str());
}

TEST_F(BstUnitTestSuite, PostOrderFirstAndLastTraverseTreeTest1) {
  std::ostringstream real_traversal;
  std::ostringstream iterator_traversal;
  BST<int32_t> bst{};
  size_t size = 10000;
  std::vector<int32_t> values = GetRandomNumbers(size);

  for (int32_t& value : values) {
    bst.insert(value);
  }

  auto it = bst.end<PostOrder>();
  auto reverse_it = bst.rend<PostOrder>();

  ASSERT_EQ(*--it, *bst.rbegin<PostOrder>());
  ASSERT_EQ(*--reverse_it, *bst.begin<PostOrder>());
}

TEST_F(BstUnitTestSuite, PostOrderTraverseTreeBothWaysTest1) {
  std::ostringstream reversed_traversal;
  std::ostringstream iterator_traversal;
  BST<int32_t> bst{};
  size_t size = 10000;
  std::vector<int32_t> values = GetRandomNumbers(size);

  for (int32_t& value : values) {
    bst.insert(value);
  }

  for (auto it = bst.rbegin<PostOrder>(); it != bst.rend<PostOrder>(); ++it) {
    reversed_traversal << *it << ' ';
  }

  for (auto it = --bst.end<PostOrder>(); it != bst.end<PostOrder>(); --it) {
    iterator_traversal << *it << ' ';
  }

  ASSERT_EQ(reversed_traversal.str(), iterator_traversal.str());
}
