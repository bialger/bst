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

  for (const auto& val : bst) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(values, data_inorder);
}


