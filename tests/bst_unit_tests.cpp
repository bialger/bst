#include <sstream>

#include <vector>
#include <set>
#include <gtest/gtest.h>

#include "test_functions.hpp"
#include "BstUnitTestSuite.hpp"

using namespace bialger;

TEST_F(BstUnitTestSuite, EmptyTest) {
  BST<int32_t> empty_bst;
  ASSERT_EQ(empty_bst, empty_bst);
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
  bst.insert({3, 5, 4, 5, 2, 5, 1});

  ASSERT_EQ(bst.size(), sample_values.size());

  for (const int32_t& val : bst) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(sample_values, data_inorder);
}

TEST_F(BstUnitTestSuite, InsertTest3) {
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

TEST_F(BstUnitTestSuite, InsertTest4) {
  std::vector<int32_t> data_inorder;
  bst.insert(values_unique.begin(), values_unique.end());

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
  BST<int32_t, LessContainer<void>, CountingAllocator<int32_t>> bst2;
  bst2.insert(bst);

  ASSERT_EQ(bst2.size(), values_unique.size());

  for (const int32_t& val : bst2) {
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
  size_t erase_count = 0;

  for (int32_t value : values) {
    ASSERT_EQ(*bst.find(value), value);
    ASSERT_EQ(*bst.find<PreOrder>(value), value);
    ASSERT_EQ(*bst.find<PostOrder>(value), value);
  }
}

TEST_F(BstUnitTestSuite, FindTest2) {
  std::vector<int32_t> data_inorder;
  bst.insert(values_unique);
  size_t erase_count = 0;

  for (int32_t value : values_unique) {
    ASSERT_TRUE(bst.find(value + 1000000) == bst.end());
    ASSERT_TRUE(bst.find<PreOrder>(value + 1000000) == bst.end<PreOrder>());
    ASSERT_TRUE(bst.find<PostOrder>(value + 1000000) == bst.end<PostOrder>());
  }
}
