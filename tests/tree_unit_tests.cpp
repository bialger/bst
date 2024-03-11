#include <sstream>

#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <gtest/gtest.h>

#include "test_functions.hpp"
#include "TreeUnitTestSuite.hpp"

using namespace bialger;

using IntTree = BinarySearchTree<int32_t, int32_t*, std::less<>, std::equal_to<>, std::allocator<int32_t>>;
using StringTree = BinarySearchTree<std::string,
                                    std::string*,
                                    std::less<std::string>,
                                    std::equal_to<>,
                                    std::allocator<std::string>>;

using UnstrictIntTree = BinarySearchTree<int32_t,
                                         int32_t*,
                                         std::less_equal<>,
                                         std::equal_to<>,
                                         std::allocator<int32_t>>;
using UnstrictStringTree = BinarySearchTree<std::string,
                                    std::string*,
                                    std::less_equal<std::string>,
                                    std::equal_to<>,
                                    std::allocator<std::string>>;

TEST_F(TreeUnitTestSuite, EmptyTreeTest) {
  IntTree bst{};
}

TEST_F(TreeUnitTestSuite, InsertTreeTest1) {
  IntTree bst{};
  std::vector<int32_t> values{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  ASSERT_EQ(bst.GetSize(), values.size());
}

TEST_F(TreeUnitTestSuite, InsertTreeTest2) {
  StringTree bst{};
  std::vector<std::string> values{"test", "test1", "t", "_", "", "r"};

  for (std::string& value : values) {
    bst.Insert(value, &value);
  }

  ASSERT_EQ(bst.GetSize(), values.size());
}

TEST_F(TreeUnitTestSuite, InsertTreeTest3) {
  StringTree bst(true);
  std::vector<std::string> values{"test", "test1", "t", "test", "_", "", "r"};

  for (std::string& value : values) {
    bst.Insert(value, &value);
  }

  ASSERT_EQ(bst.GetSize(), values.size());
}

TEST_F(TreeUnitTestSuite, InsertTreeTest4) {
  IntTree bst{};
  size_t size = 1000;
  std::vector<int32_t> values = GetRandomNumbers(size);

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }
}

TEST_F(TreeUnitTestSuite, InsertTreeTest5) {
  IntTree bst{};
  size_t size = 1000;
  std::random_device dev;
  std::mt19937 rng(dev());
  std::vector<int32_t> values(size);

  for (int32_t i = 0; i < size; ++i) {
    values[i] = i;
  }

  std::shuffle(values.begin(), values.end(), rng);

  for (int32_t& value : values) {
    ITreeNode* new_node = bst.Insert(value, &value);
    ASSERT_EQ(new_node, bst.FindFirst(value));
  }
}

TEST_F(TreeUnitTestSuite, InsertTreeTest6) {
  IntTree bst{};
  size_t size = 1000;
  std::vector<int32_t> values_tmp = GetRandomNumbers(size);
  std::vector<int32_t> values(values_tmp);
  std::random_device dev;
  std::mt19937 rng(dev());

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  size_t unique = bst.GetSize();
  values.insert(values.end(), values_tmp.begin(), values_tmp.end());
  std::shuffle(values.begin(), values.end(), rng);

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  ASSERT_EQ(bst.GetSize(), unique);
}

TEST_F(TreeUnitTestSuite, InsertTreeTest7) {
  IntTree bst(true);
  size_t size = 1000;
  std::vector<int32_t> values_tmp = GetRandomNumbers(size);
  std::vector<int32_t> values(values_tmp);
  std::random_device dev;
  std::mt19937 rng(dev());

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  values.insert(values.end(), values_tmp.begin(), values_tmp.end());
  std::shuffle(values.begin(), values.end(), rng);

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  ASSERT_EQ(bst.GetSize(), 3 * size);
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

TEST_F(TreeUnitTestSuite, FindNextTreeTest1) {
  IntTree bst{};
  size_t size = 1000;
  std::vector<int32_t> values(size);
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type>
      dist(0, std::numeric_limits<uint32_t>::max());

  for (int32_t i = 0; i < 4 * size; i += 4) {
    values[i / 4] = i + static_cast<int32_t>(dist(rng) % 4);
  }

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  for (int32_t i = 0; i < 4 * size; ++i) {
    auto vector_lower = std::lower_bound(values.begin(), values.end(), i);
    auto* bst_find = dynamic_cast<IntTree::NodeType*>(bst.FindFirst(i));
    auto* bst_next = dynamic_cast<IntTree::NodeType*>(bst.FindNext(i));
    if (vector_lower == values.end()) {
      ASSERT_EQ(bst_find, bst.GetEnd());
      ASSERT_EQ(bst_next, bst.GetEnd());
    } else if (bst_find != nullptr) {
      ASSERT_EQ(bst_find->key, *vector_lower);
    } else {
      ASSERT_EQ(bst_next->key, *vector_lower);
    }
  }
}

TEST_F(TreeUnitTestSuite, FindNextTreeTest2) {
  IntTree bst{};
  size_t size = 1000;
  std::vector<int32_t> values(size);
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type>
      dist(0, std::numeric_limits<uint32_t>::max());

  for (int32_t i = 0; i < 4 * size; i += 4) {
    values[i / 4] = i + static_cast<int32_t>(dist(rng) % 4);
  }

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  for (int32_t i = 0; i < 4 * size; ++i) {
    auto vector_upper = std::upper_bound(values.begin(), values.end(), i);
    auto* bst_next = dynamic_cast<IntTree::NodeType*>(bst.FindNext(i));
    if (vector_upper == values.end()) {
      ASSERT_EQ(bst_next, bst.GetEnd());
    } else {
      ASSERT_EQ(bst_next->key, *vector_upper);
    }
  }
}

TEST_F(TreeUnitTestSuite, InsertUnstrictTreeTest1) {
  UnstrictStringTree bst{};
  std::vector<std::string> values{"test", "test1", "t", "_", "", "r"};

  for (std::string& value : values) {
    bst.Insert(value, &value);
  }

  ASSERT_EQ(bst.GetSize(), values.size());
}

TEST_F(TreeUnitTestSuite, InsertUnstrictTreeTest2) {
  UnstrictStringTree bst(true);
  std::vector<std::string> values{"test", "test1", "t", "r", "test", "_", "", "r"};

  for (std::string& value : values) {
    bst.Insert(value, &value);
  }

  ASSERT_EQ(bst.GetSize(), values.size());
}

TEST_F(TreeUnitTestSuite, InsertTreeUnstrictTest3) {
  UnstrictIntTree bst{};
  size_t size = 1000;
  std::random_device dev;
  std::mt19937 rng(dev());
  std::vector<int32_t> values(size);

  for (int32_t i = 0; i < size; ++i) {
    values[i] = i;
  }

  std::shuffle(values.begin(), values.end(), rng);

  for (int32_t& value : values) {
    ITreeNode* new_node = bst.Insert(value, &value);
    ASSERT_EQ(new_node, bst.FindFirst(value));
  }
}

TEST_F(TreeUnitTestSuite, InsertTreeUnstrictTest4) {
  UnstrictIntTree bst{};
  size_t size = 1000;
  std::vector<int32_t> values_tmp = GetRandomNumbers(size);
  std::vector<int32_t> values(values_tmp);
  std::random_device dev;
  std::mt19937 rng(dev());

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  size_t unique = bst.GetSize();
  values.insert(values.end(), values_tmp.begin(), values_tmp.end());
  std::shuffle(values.begin(), values.end(), rng);

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  ASSERT_EQ(bst.GetSize(), unique);
}

TEST_F(TreeUnitTestSuite, InsertTreeUnstrictTest5) {
  UnstrictIntTree bst(true);
  size_t size = 1000;
  std::vector<int32_t> values_tmp = GetRandomNumbers(size);
  std::vector<int32_t> values(values_tmp);
  std::random_device dev;
  std::mt19937 rng(dev());

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  values.insert(values.end(), values_tmp.begin(), values_tmp.end());
  std::shuffle(values.begin(), values.end(), rng);

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  ASSERT_EQ(bst.GetSize(), 3 * size);
}

TEST_F(TreeUnitTestSuite, CopyUnstrictTreeTest1) {
  UnstrictIntTree bst{};
  size_t size = 1000;
  std::vector<int32_t> values = GetRandomNumbers(size);

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  UnstrictIntTree bst2 = bst;

  for (int32_t& value : values) {
    ASSERT_TRUE(bst.Contains(value));
    ASSERT_TRUE(bst2.Contains(value));
    ASSERT_NE(bst.FindFirst(value), bst2.FindFirst(value));
  }
}

TEST_F(TreeUnitTestSuite, CopyTreeUnstrictTest2) {
  UnstrictIntTree bst{};
  UnstrictIntTree bst2{};
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

TEST_F(TreeUnitTestSuite, DeleteTreeUnstrictTest1) {
  UnstrictStringTree bst{};
  std::vector<std::string> values{"test", "test1", "t", "_", "", "r", "r", "abcdef", "1"};
  std::random_device dev;
  std::mt19937 rng(dev());

  for (std::string& value : values) {
    bst.Insert(value, &value);
  }

  std::shuffle(values.begin(), values.end(), rng);

  for (std::string& value : values) {
    bst.Delete(bst.FindFirst(value));
  }

  ASSERT_EQ(bst.GetRoot(), nullptr);
  ASSERT_EQ(bst.GetSize(), 0);
}

TEST_F(TreeUnitTestSuite, DeleteUnstrictTreeTest2) {
  UnstrictIntTree bst{};
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

TEST_F(TreeUnitTestSuite, DeleteUnstrictTreeTest3) {
  UnstrictIntTree bst(true);
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

TEST_F(TreeUnitTestSuite, FindNextUnstrictTreeTest1) {
  UnstrictIntTree bst{};
  size_t size = 1000;
  std::vector<int32_t> values(size);
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type>
      dist(0, std::numeric_limits<uint32_t>::max());

  for (int32_t i = 0; i < 4 * size; i += 4) {
    values[i / 4] = i + static_cast<int32_t>(dist(rng) % 4);
  }

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  for (int32_t i = 0; i < 4 * size; ++i) {
    auto vector_lower = std::lower_bound(values.begin(), values.end(), i);
    auto* bst_find = dynamic_cast<UnstrictIntTree::NodeType*>(bst.FindFirst(i));
    auto* bst_next = dynamic_cast<UnstrictIntTree::NodeType*>(bst.FindNext(i));
    if (vector_lower == values.end()) {
      ASSERT_EQ(bst_find, bst.GetEnd());
      ASSERT_EQ(bst_next, bst.GetEnd());
    } else if (bst_find != nullptr) {
      ASSERT_EQ(bst_find->key, *vector_lower);
    } else {
      ASSERT_EQ(bst_next->key, *vector_lower);
    }
  }
}

TEST_F(TreeUnitTestSuite, FindNextUnstrictTreeTest2) {
  UnstrictIntTree bst{};
  size_t size = 1000;
  std::vector<int32_t> values(size);
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type>
      dist(0, std::numeric_limits<uint32_t>::max());

  for (int32_t i = 0; i < 4 * size; i += 4) {
    values[i / 4] = i + static_cast<int32_t>(dist(rng) % 4);
  }

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  for (int32_t i = 0; i < 4 * size; ++i) {
    auto vector_upper = std::upper_bound(values.begin(), values.end(), i);
    auto* bst_next = dynamic_cast<UnstrictIntTree::NodeType*>(bst.FindNext(i));
    if (vector_upper == values.end()) {
      ASSERT_EQ(bst_next, bst.GetEnd());
    } else {
      ASSERT_EQ(bst_next->key, *vector_upper);
    }
  }
}
