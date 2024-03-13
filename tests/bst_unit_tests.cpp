#include <sstream>

#include "test_functions.hpp"
#include "BstUnitTestSuite.hpp"

#include <vector>
#include <set>
#include <gtest/gtest.h>

using namespace bialger;

TEST_F(BstUnitTestSuite, EmptyTest) {
  BST<int32_t> empty_bst;
  ASSERT_EQ(empty_bst, empty_bst);
  ASSERT_EQ(empty_bst.size(), 0);
  ASSERT_TRUE(empty_bst.empty());
  ASSERT_FALSE(empty_bst.contains(0));
}

TEST_F(BstUnitTestSuite, InsertTest1) {
  std::vector<int32_t> sample_values = {1, 2, 3, 4, 5};
  std::vector<int32_t> data_inorder;

  for (int32_t& value : sample_values) {
    bst.insert(value);
  }

  ASSERT_EQ(bst.size(), sample_values.size());

  for (const int32_t& val : bst) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(sample_values, data_inorder);
}

TEST_F(BstUnitTestSuite, ConstructTest1) {
  std::vector<int32_t> sample_values = {1, 2, 3, 4, 5};
  std::vector<int32_t> data_inorder;
  BST<int32_t> bst2 = {1, 2, 3, 4, 5};

  ASSERT_EQ(bst2.size(), sample_values.size());

  for (const int32_t& val : bst2) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(sample_values, data_inorder);
}

TEST_F(BstUnitTestSuite, ConstructTest2) {
  std::vector<int32_t> sample_values = {1, 2, 3, 4, 5};
  std::vector<int32_t> data_inorder;
  BST<int32_t> bst2(sample_values.begin(), sample_values.end());

  ASSERT_EQ(bst2.size(), sample_values.size());

  for (const int32_t& val : bst2) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(sample_values, data_inorder);
}

TEST_F(BstUnitTestSuite, CopyTest1) {
  std::vector<int32_t> sample_values = {1, 2, 3, 4, 5};
  std::vector<int32_t> data_inorder;

  for (int32_t& value : sample_values) {
    bst.insert(value);
  }

  BST<int32_t> bst2 = bst;

  ASSERT_EQ(bst2.size(), sample_values.size());

  for (const int32_t& val : bst2) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(sample_values, data_inorder);
}

TEST_F(BstUnitTestSuite, CopyTest2) {
  std::vector<int32_t> sample_values = {1, 2, 3, 4, 5};
  std::vector<int32_t> data_inorder;
  BST<int32_t> bst2;

  for (int32_t& value : sample_values) {
    bst2.insert(value);
  }

  bst = bst2;

  ASSERT_EQ(bst.size(), sample_values.size());

  for (const int32_t& val : bst) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(sample_values, data_inorder);
}

TEST_F(BstUnitTestSuite, CopyTest3) {
  std::vector<int32_t> sample_values = {1, 2, 3, 4, 5};
  std::vector<int32_t> data_inorder;
  bst = {1, 2, 3, 4, 5};

  ASSERT_EQ(bst.size(), sample_values.size());

  for (const int32_t& val : bst) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(sample_values, data_inorder);
}
