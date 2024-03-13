#include <vector>
#include <set>

#include "lib/bst/BST.hpp"
#include <gtest/gtest.h>

using namespace bialger;

TEST(StaticAssertionTestSuite, IsIteratorTest1) {
  ASSERT_TRUE(is_iterator<std::vector<int32_t>::iterator>::value);
  ASSERT_TRUE(is_iterator<std::vector<int32_t>::const_iterator>::value);
  ASSERT_TRUE(is_iterator<std::set<int32_t>::iterator>::value);
  ASSERT_TRUE(is_iterator<std::set<int32_t>::const_iterator>::value);
}

TEST(StaticAssertionTestSuite, IsIteratorTest2) {
  ASSERT_FALSE(is_iterator<std::vector<int32_t>>::value);
  ASSERT_FALSE(is_iterator<int32_t>::value);
  ASSERT_FALSE(is_iterator<std::set<int32_t>>::value);
  ASSERT_FALSE(is_iterator<std::string>::value);
}

TEST(StaticAssertionTestSuite, IsIteratorTest3) {
  ASSERT_TRUE(is_iterator<BST<int32_t>::iterator>::value);
  ASSERT_TRUE(is_iterator<BST<int32_t>::const_iterator>::value);
  ASSERT_TRUE(is_iterator<BST<int32_t>::reverse_iterator>::value);
  ASSERT_TRUE(is_iterator<BST<int32_t>::const_reverse_iterator>::value);
}

TEST(StaticAssertionTestSuite, IsIterableTest1) {
  ASSERT_TRUE(is_iterable<std::vector<int32_t>>::value);
  ASSERT_TRUE(is_iterable<std::set<std::string>>::value);
  ASSERT_TRUE(is_iterable<std::string>::value);
}

TEST(StaticAssertionTestSuite, IsIterableTest2) {
  ASSERT_FALSE(is_iterable<std::vector<int32_t>::iterator>::value);
  ASSERT_FALSE(is_iterable<int32_t>::value);
  ASSERT_FALSE(is_iterable<std::set<int32_t>::iterator>::value);
}

TEST(StaticAssertionTestSuite, IsIterableTest3) {
  ASSERT_TRUE(is_iterable<BST<int32_t>>::value);
  ASSERT_TRUE(is_iterable<BST<std::string>>::value);
}