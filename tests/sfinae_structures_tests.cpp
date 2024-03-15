#include <vector>
#include <set>

#include "lib/bst/bst_sfinae.hpp"
#include "lib/tree/tree_sfinae.hpp"
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

TEST(StaticAssertionTestSuite, ComparatorTransparentTest1) {
  ASSERT_TRUE(comparator_transparent<std::less<>>::value);
  ASSERT_TRUE(comparator_transparent<std::equal_to<>>::value);
  ASSERT_TRUE(comparator_transparent<std::less_equal<>>::value);
}

TEST(StaticAssertionTestSuite, ComparatorTransparentTest2) {
  ASSERT_FALSE(comparator_transparent<std::less<std::string>>::value);
  ASSERT_FALSE(comparator_transparent<std::equal_to<int32_t>>::value);
  ASSERT_FALSE(comparator_transparent<std::less_equal<std::set<int32_t>>>::value);
}

TEST(StaticAssertionTestSuite, AreComparableTest1) {
  bool int_long_less = are_comparable<std::less<>, int32_t, int64_t>::value;
  bool char_size_less = are_comparable<std::less<>, char, size_t>::value;
  bool uint16_int64_equals = are_comparable<std::equal_to<>, uint16_t, int64_t>::value;
  bool strings_less_eq = are_comparable<std::less_equal<std::string>, std::string, std::string>::value;
  ASSERT_TRUE(int_long_less);
  ASSERT_TRUE(char_size_less);
  ASSERT_TRUE(uint16_int64_equals);
  ASSERT_TRUE(strings_less_eq);
}

TEST(StaticAssertionTestSuite, AreComparableTest2) {
  bool ints_string_less = are_comparable<std::less<int32_t>, int32_t, std::string>::value;
  bool bst_vector_less = are_comparable<std::less<>, BST<std::string>, std::vector<char>>::value;
  bool string_int64_equals = are_comparable<std::equal_to<>, std::string, int64_t>::value;
  bool int_strings_less_eq = are_comparable<std::less_equal<std::string>, int32_t, int32_t>::value;
  ASSERT_FALSE(ints_string_less);
  ASSERT_FALSE(bst_vector_less);
  ASSERT_FALSE(string_int64_equals);
  ASSERT_FALSE(int_strings_less_eq);
}
