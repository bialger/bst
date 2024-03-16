#include <sstream>

#include <vector>
#include <set>
#include <gtest/gtest.h>

#include "BstUnitTestSuite.hpp"

using namespace bialger;

TEST_F(BstUnitTestSuite, EmptyTest) {
  BST<int32_t> empty_bst;
  empty_bst.insert({});
  empty_bst.insert(values.end(), values.end());
  empty_bst.insert(custom_bst);
  ASSERT_EQ(empty_bst, bst);
  ASSERT_EQ(empty_bst.size(), 0);
  ASSERT_TRUE(empty_bst.empty());
  ASSERT_FALSE(empty_bst.contains(0));
}

TEST_F(BstUnitTestSuite, NonEmptyTest) {
  bst.insert(0);
  ASSERT_EQ(bst, bst);
  ASSERT_EQ(bst.size(), 1);
  ASSERT_FALSE(bst.empty());
}

TEST_F(BstUnitTestSuite, BeginTest) {
  BST<std::string> string_bst;
  std::string element = "str";
  string_bst.insert(element);
  ASSERT_TRUE(string_bst.begin() == string_bst.begin<InOrder>());
  ASSERT_EQ(*string_bst.begin(), element);
  ASSERT_EQ(*string_bst.begin<PreOrder>(), element);
  ASSERT_EQ(*string_bst.begin<PostOrder>(), element);
  ASSERT_EQ(*string_bst.cbegin(), element);
  ASSERT_EQ(*string_bst.cbegin<PreOrder>(), element);
  ASSERT_EQ(*string_bst.cbegin<PostOrder>(), element);
  ASSERT_EQ(*string_bst.rbegin(), element);
  ASSERT_EQ(*string_bst.rbegin<PreOrder>(), element);
  ASSERT_EQ(*string_bst.rbegin<PostOrder>(), element);
  ASSERT_EQ(*string_bst.crbegin(), element);
  ASSERT_EQ(*string_bst.crbegin<PreOrder>(), element);
  ASSERT_EQ(*string_bst.crbegin<PostOrder>(), element);
}

TEST_F(BstUnitTestSuite, IteratorTest) {
  BST<std::string> string_bst;
  std::string element = "str";
  string_bst.insert(element);

  auto current = string_bst.begin();
  auto next = string_bst.end();
  ASSERT_TRUE(next == current.next());
  ASSERT_TRUE(next.prev() == current);
  ASSERT_TRUE(next.prev() == current++);
  ASSERT_TRUE(next == current);
  ASSERT_EQ(*--current, element);
  ASSERT_EQ(current->size(), element.size());
  ASSERT_EQ(current++->size(), element.size());
}

TEST_F(BstUnitTestSuite, IteratorTest2) {
  BST<std::string> string_bst;
  std::string element = "str";
  string_bst.insert(element);

  auto current = string_bst.begin();
  auto next = string_bst.end();
  ASSERT_TRUE(*current-- == element);
  ASSERT_THROW(current++, std::out_of_range);
  ASSERT_THROW(++current, std::out_of_range);
  ASSERT_TRUE(--current == string_bst.begin());
  ASSERT_TRUE(--current == next);
}

TEST_F(BstUnitTestSuite, BadComparatorTest) {
  BST<int32_t, std::less_equal<>> bad_bst;
  ASSERT_THROW(bad_bst.insert(0), std::invalid_argument);
  ASSERT_THROW(bad_bst.insert(bad_bst.end(), 0), std::invalid_argument);
  ASSERT_THROW(bad_bst.insert({1}), std::invalid_argument);
  ASSERT_THROW(bad_bst.insert(values_unique.begin(), values_unique.end()), std::invalid_argument);
  ASSERT_THROW(bad_bst.insert(values_unique), std::invalid_argument);
}

TEST_F(BstUnitTestSuite, ConstructTest1) {
  std::vector<int32_t> sample_values = {1, 2, 3, 4, 5};
  std::vector<int32_t> data_inorder;
  BST<int32_t> bst2(default_comparator, default_allocator);

  for (int32_t& value : sample_values) {
    bst2.insert(value);
  }

  ASSERT_EQ(bst2.size(), sample_values.size());
  ASSERT_EQ(default_allocator, bst2.get_allocator());

  for (const int32_t& val : bst2) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(sample_values, data_inorder);
}

TEST_F(BstUnitTestSuite, ConstructTest2) {
  std::vector<int32_t> sample_values = {1, 2, 3, 4, 5};
  std::vector<int32_t> data_inorder;
  BST<int32_t> bst2 = {1, 2, 3, 4, 5};

  ASSERT_EQ(bst2.size(), sample_values.size());

  for (const int32_t& val : bst2) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(sample_values, data_inorder);
}

TEST_F(BstUnitTestSuite, ConstructTest3) {
  std::vector<int32_t> sample_values = {1, 2, 3, 4, 5};
  std::vector<int32_t> data_inorder;
  BST<int32_t> bst2(sample_values.begin(), sample_values.end());

  ASSERT_EQ(bst2.size(), sample_values.size());

  for (const int32_t& val : bst2) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(sample_values, data_inorder);
}

TEST_F(BstUnitTestSuite, EqualComparatorAllocatorTest1) {
  std::vector<int32_t> sample_values = {1, 2, 3, 4, 5};
  std::vector<int32_t> data_inorder;
  BST<int32_t, LessContainer<void>, CountingAllocator<int32_t>> bst2(custom_allocator);

  for (int32_t& value : sample_values) {
    bst2.insert(value);
  }

  ASSERT_EQ(bst2.size(), sample_values.size());
  ASSERT_EQ(custom_allocator, bst2.get_allocator());

  for (const int32_t& val : bst2) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(sample_values, data_inorder);
}

TEST_F(BstUnitTestSuite, EqualComparatorAllocatorTest2) {
  std::vector<int32_t> sample_values = {1, 2, 3, 4, 5};
  std::vector<int32_t> data_inorder;
  BST<int32_t, LessContainer<void>, CountingAllocator<int32_t>>
      bst2({1, 2, 3, 4, 5}, custom_comparator, custom_allocator);

  ASSERT_EQ(bst2.size(), sample_values.size());
  ASSERT_EQ(custom_comparator, bst2.key_comp());
  ASSERT_EQ(custom_comparator, bst2.value_comp());
  ASSERT_EQ(custom_allocator, bst2.get_allocator());

  for (const int32_t& val : bst2) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(sample_values, data_inorder);
}

TEST_F(BstUnitTestSuite, EqualComparatorAllocatorTest3) {
  std::vector<int32_t> sample_values = {1, 2, 3, 4, 5};
  std::vector<int32_t> data_inorder;
  BST<int32_t, LessContainer<void>, CountingAllocator<int32_t>> bst2({1, 2, 3, 4, 5}, custom_allocator);

  ASSERT_EQ(bst2.size(), sample_values.size());
  ASSERT_EQ(custom_allocator, bst2.get_allocator());

  for (const int32_t& val : bst2) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(sample_values, data_inorder);
}

TEST_F(BstUnitTestSuite, EqualComparatorAllocatorTest4) {
  std::vector<int32_t> sample_values = {1, 2, 3, 4, 5};
  std::vector<int32_t> data_inorder;
  BST<int32_t, LessContainer<void>, CountingAllocator<int32_t>>
      bst2({1, 2, 3, 4, 5}, custom_comparator, custom_allocator);

  ASSERT_EQ(bst2.size(), sample_values.size());
  ASSERT_EQ(custom_comparator, bst2.key_comp());
  ASSERT_EQ(custom_allocator, bst2.get_allocator());

  for (const int32_t& val : bst2) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(sample_values, data_inorder);
}

TEST_F(BstUnitTestSuite, EqualComparatorAllocatorTest5) {
  std::vector<int32_t> sample_values = {1, 2, 3, 4, 5};
  std::vector<int32_t> data_inorder;
  BST<int32_t, LessContainer<void>, CountingAllocator<int32_t>>
      bst2(sample_values.begin(), sample_values.end(), custom_allocator);

  ASSERT_EQ(bst2.size(), sample_values.size());
  ASSERT_EQ(custom_allocator, bst2.get_allocator());

  for (const int32_t& val : bst2) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(sample_values, data_inorder);
}

TEST_F(BstUnitTestSuite, EqualComparatorAllocatorTest6) {
  std::vector<int32_t> sample_values = {1, 2, 3, 4, 5};
  std::vector<int32_t> data_inorder;
  BST<int32_t, LessContainer<void>, CountingAllocator<int32_t>>
      bst2(sample_values.begin(), sample_values.end(), custom_comparator, custom_allocator);

  for (int32_t& value : sample_values) {
    bst2.insert(value);
  }

  ASSERT_EQ(bst2.size(), sample_values.size());
  ASSERT_EQ(custom_comparator, bst2.key_comp());
  ASSERT_EQ(custom_allocator, bst2.get_allocator());

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

TEST_F(BstUnitTestSuite, EqualCopyComparatorAllocatorTest1) {
  std::vector<int32_t> sample_values = {1, 2, 3, 4, 5};
  std::vector<int32_t> data_inorder;
  custom_bst.insert(sample_values.begin(), sample_values.end());

  BST<int32_t, LessContainer<void>, CountingAllocator<int32_t>> bst2 = custom_bst;
  ASSERT_EQ(bst2.size(), sample_values.size());
  ASSERT_EQ(custom_bst.get_allocator(), bst2.get_allocator());
  ASSERT_EQ(custom_bst.key_comp(), bst2.key_comp());

  for (const int32_t& val : bst2) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(sample_values, data_inorder);
}

TEST_F(BstUnitTestSuite, EqualCopyComparatorAllocatorTest2) {
  std::vector<int32_t> sample_values = {1, 2, 3, 4, 5};
  std::vector<int32_t> data_inorder;
  custom_bst.insert(sample_values.begin(), sample_values.end());

  BST<int32_t, LessContainer<void>, CountingAllocator<int32_t>> bst2;
  bst2 = custom_bst;

  ASSERT_EQ(bst2.size(), sample_values.size());
  ASSERT_EQ(custom_bst.get_allocator(), bst2.get_allocator());
  ASSERT_EQ(custom_bst.key_comp(), bst2.key_comp());

  for (const int32_t& val : bst2) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(sample_values, data_inorder);
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

TEST_F(BstUnitTestSuite, InsertTest2) {
  std::vector<int32_t> sample_values = {1, 2, 3, 4, 5};
  std::vector<int32_t> data_inorder;

  for (int32_t& value : sample_values) {
    bst.insert(bst.end(), value);
  }

  ASSERT_EQ(bst.size(), sample_values.size());

  for (const int32_t& val : bst) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(sample_values, data_inorder);
}

TEST_F(BstUnitTestSuite, InsertTest3) {
  std::vector<int32_t> sample_values = {1, 2, 3, 4, 5};
  std::vector<int32_t> data_inorder;
  bst.insert({3, 5, 4, 5, 2, 5, 1});

  ASSERT_EQ(bst.size(), sample_values.size());

  for (const int32_t& val : bst) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(sample_values, data_inorder);
}

TEST_F(BstUnitTestSuite, InsertTest4) {
  std::vector<int32_t> data_inorder;

  for (int32_t& value : values_unique) {
    bst.insert(value);
  }

  ASSERT_EQ(bst.size(), values_unique.size());

  for (const int32_t& val : bst) {
    data_inorder.push_back(val);
  }

  std::sort(values_unique.begin(), values_unique.end());

  ASSERT_EQ(values_unique, data_inorder);
}

TEST_F(BstUnitTestSuite, InsertTest5) {
  std::vector<int32_t> data_inorder;
  bst.insert(values_unique.begin(), values_unique.end());

  ASSERT_EQ(bst.size(), values_unique.size());

  for (const int32_t& val : bst) {
    data_inorder.push_back(val);
  }

  std::sort(values_unique.begin(), values_unique.end());

  ASSERT_EQ(values_unique, data_inorder);
}

TEST_F(BstUnitTestSuite, InsertTest6) {
  std::vector<int32_t> data_inorder;
  bst.insert(values_unique);

  ASSERT_EQ(bst.size(), values_unique.size());

  for (const int32_t& val : bst) {
    data_inorder.push_back(val);
  }

  std::sort(values_unique.begin(), values_unique.end());

  ASSERT_EQ(values_unique, data_inorder);
}

TEST_F(BstUnitTestSuite, InsertTest7) {
  std::vector<int32_t> data_inorder;
  std::vector<int32_t> data_inorder2;
  custom_bst.insert(values);
  BST<int32_t, LessContainer<void>, CountingAllocator<int32_t>> bst2;
  bst2.insert(custom_bst);

  ASSERT_EQ(bst2.size(), custom_bst.size());

  for (const int32_t& val : custom_bst) {
    data_inorder.push_back(val);
  }

  for (const int32_t& val : bst2) {
    data_inorder2.push_back(val);
  }

  ASSERT_EQ(data_inorder, data_inorder2);
}

TEST_F(BstUnitTestSuite, InsertTest8) {
  std::vector<int32_t> data_inorder;
  bst.insert(values_unique);

  ASSERT_EQ(bst.size(), values_unique.size());

  for (const int32_t& val : bst) {
    data_inorder.push_back(val);
  }

  std::sort(values_unique.begin(), values_unique.end());

  ASSERT_EQ(values_unique, data_inorder);
}

TEST_F(BstUnitTestSuite, ClearTest) {
  std::vector<int32_t> data_inorder;
  bst.insert(values);

  bst.clear();

  ASSERT_EQ(bst.size(), 0);
}

TEST_F(BstUnitTestSuite, EraseTest1) {
  std::vector<int32_t> data_inorder;
  bst.insert(values);

  for (auto it = bst.begin(); it != bst.end();) {
    auto current = it++;
    bst.erase(current);
  }

  ASSERT_EQ(bst.size(), 0);
}

TEST_F(BstUnitTestSuite, EraseTest2) {
  std::vector<int32_t> data_inorder;
  bst.insert(values_unique);
  size_t erase_count = 0;

  for (auto it = bst.begin(); it != bst.end();) {
    auto current = it++;

    if (dist(rng) % 2 == 0) {
      bst.erase(current);
      ++erase_count;
    }
  }

  ASSERT_EQ(bst.size(), size - erase_count);
}

TEST_F(BstUnitTestSuite, EraseTest3) {
  std::vector<int32_t> data_inorder;
  bst.insert(values_unique);
  const size_t erase_size = 250 + (dist(rng) % (size / 4));
  const size_t erase_start = (dist(rng) % (size / 2));
  const size_t erase_end = erase_start + erase_size;
  auto first = bst.begin();
  auto last = bst.begin();

  for (size_t i = 0; i < erase_start; ++i) {
    ++first;
  }

  for (size_t i = 0; i < erase_end; ++i) {
    ++last;
  }

  bst.erase(first, last);

  ASSERT_EQ(bst.size(), size - erase_size);
}

TEST_F(BstUnitTestSuite, EraseTest4) {
  std::vector<int32_t> data_inorder;
  bst.insert(values_unique);
  size_t erase_count = 0;

  for (int32_t value : values_unique) {
    ASSERT_EQ(bst.erase(value + 1000000), 0);
  }

  for (int32_t value : values_unique) {
    if (dist(rng) % 2 == 0) {
      ASSERT_EQ(bst.erase(value), 1);
      ++erase_count;
    }
  }

  ASSERT_EQ(bst.size(), size - erase_count);
}

TEST_F(BstUnitTestSuite, FindTest1) {
  std::vector<int32_t> data_inorder;
  bst.insert(values);

  for (int32_t value : values) {
    ASSERT_EQ(*bst.find(value), value);
    ASSERT_EQ(*bst.find<PreOrder>(value), value);
    ASSERT_EQ(*bst.find<PostOrder>(value), value);
  }
}

TEST_F(BstUnitTestSuite, FindTest2) {
  std::vector<int32_t> data_inorder;
  bst.insert(values_unique);

  for (int32_t value : values_unique) {
    ASSERT_TRUE(bst.find(value + 1000000) == bst.end());
    ASSERT_TRUE(bst.find<PreOrder>(value + 1000000) == bst.end<PreOrder>());
    ASSERT_TRUE(bst.find<PostOrder>(value + 1000000) == bst.end<PostOrder>());
  }
}

TEST_F(BstUnitTestSuite, InsertAndFindTest1) {
  std::vector<int32_t> data_inorder;

  for (int32_t& value : values_unique) {
    auto res = bst.insert(value);
    ASSERT_TRUE(res.first == bst.find(value));
    ASSERT_TRUE(res.second);
  }

  for (int32_t& value : values_unique) {
    auto res = bst.insert<PreOrder>(value);
    ASSERT_TRUE(res.first == bst.find<PreOrder>(value));
    ASSERT_FALSE(res.second);
  }

  for (int32_t& value : values_unique) {
    auto res = bst.insert<PostOrder>(value);
    ASSERT_TRUE(res.first == bst.find<PostOrder>(value));
    ASSERT_FALSE(res.second);
  }

  ASSERT_EQ(bst.size(), values_unique.size());

  for (const int32_t& val : bst) {
    data_inorder.push_back(val);
  }

  std::sort(values_unique.begin(), values_unique.end());

  ASSERT_EQ(values_unique, data_inorder);
}

TEST_F(BstUnitTestSuite, InsertAndFindTest2) {
  std::vector<int32_t> data_inorder;

  for (int32_t& value : values_unique) {
    auto res = bst.insert(bst.end(),value);
    ASSERT_TRUE(res == bst.find(value));
  }

  for (int32_t& value : values_unique) {
    auto res = bst.insert<PreOrder>(bst.end<PreOrder>(), value);
    ASSERT_TRUE(res == bst.find<PreOrder>(value));
  }

  for (int32_t& value : values_unique) {
    auto res = bst.insert<PostOrder>(bst.end<PostOrder>(), value);
    ASSERT_TRUE(res == bst.find<PostOrder>(value));
  }

  ASSERT_EQ(bst.size(), values_unique.size());

  for (const int32_t& val : bst) {
    data_inorder.push_back(val);
  }

  std::sort(values_unique.begin(), values_unique.end());

  ASSERT_EQ(values_unique, data_inorder);
}

TEST_F(BstUnitTestSuite, LowerBoundTest1) {
  std::vector<int32_t> data_inorder;
  bst.insert(values_unique);
  std::sort(values_unique.begin(), values_unique.end());

  for (int32_t value = 0; value < distance * size; ++value) {
    auto vector_lower = std::lower_bound(values_unique.begin(), values_unique.end(), value);
    auto bst_lower = bst.lower_bound(value);

    if (vector_lower != values_unique.end()) {
      ASSERT_EQ(*vector_lower, *bst_lower);
    } else {
      ASSERT_TRUE(bst_lower == bst.end());
    }
  }
}

TEST_F(BstUnitTestSuite, UpperBoundTest1) {
  std::vector<int32_t> data_inorder;
  bst.insert(values_unique);
  std::sort(values_unique.begin(), values_unique.end());

  for (int32_t value = 0; value < distance * size; ++value) {
    auto vector_upper = std::upper_bound(values_unique.begin(), values_unique.end(), value);
    auto bst_upper = bst.upper_bound(value);

    if (vector_upper != values_unique.end()) {
      ASSERT_EQ(*vector_upper, *bst_upper);
    } else {
      ASSERT_TRUE(bst_upper == bst.end());
    }
  }
}
