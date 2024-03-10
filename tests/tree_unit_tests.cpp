#include <sstream>

#include "test_functions.hpp"
#include "TreeUnitTestSuite.hpp"

#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>
#include <random>

TEST_F(TreeUnitTestSuite, EmptyTreeTest) {
  bialger::BinarySearchTree<int32_t, int32_t&, std::less<>, std::equal_to<>, std::allocator<int32_t>> bst{};
}

TEST_F(TreeUnitTestSuite, InsertTreeTest1) {
  bialger::BinarySearchTree<int32_t, int32_t&, std::less<>, std::equal_to<>, std::allocator<int32_t>> bst{};
  std::vector<int32_t> values{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

  for (int32_t& value : values) {
    bst.Insert(value, value);
  }
}

TEST_F(TreeUnitTestSuite, InsertTreeTest2) {
  bialger::BinarySearchTree<std::string, std::string*, std::less<>, std::equal_to<>, std::allocator<std::string>> bst{};
  std::vector<std::string> values{"test", "test1", "t", "_", "", "r"};

  for (std::string& value : values) {
    bst.Insert(value, &value);
  }
}

TEST_F(TreeUnitTestSuite, InsertTreeTest3) {
  bialger::BinarySearchTree<std::string, std::string*, std::less<>, std::equal_to<>, std::allocator<std::string>>
      bst(true);
  std::vector<std::string> values{"test", "test1", "t", "test", "_", "", "r"};

  for (std::string& value : values) {
    bst.Insert(value, &value);
  }
}

TEST_F(TreeUnitTestSuite, InsertTreeTest4) {
  bialger::BinarySearchTree<int32_t, int32_t&, std::less<>, std::equal_to<>, std::allocator<int32_t>> bst{};
  size_t size = 1000;
  std::vector<int32_t> values = GetRandomNumbers(size);

  for (int32_t& value : values) {
    bst.Insert(value, value);
  }
}

TEST_F(TreeUnitTestSuite, DeleteTreeTest1) {
  bialger::BinarySearchTree<std::string, std::string*, std::less<>, std::equal_to<>, std::allocator<std::string>> bst{};
  std::vector<std::string> values{"test", "test1", "t", "_", "", "r"};

  for (std::string& value : values) {
    bst.Insert(value, &value);
  }

  for (std::string& value : values) {
    bst.Delete(bst.FindFirst(value));
  }
}

TEST_F(TreeUnitTestSuite, DeleteTreeTest2) {
  bialger::BinarySearchTree<std::string, std::string*, std::less<>, std::equal_to<>, std::allocator<std::string>> bst{};
  std::vector<std::string> values{"test", "test1", "t", "_", "", "r", "r", "abcdef", "1"};

  for (std::string& value : values) {
    bst.Insert(value, &value);
  }

  std::reverse(values.begin(), values.end());

  for (std::string& value : values) {
    bst.Delete(bst.FindFirst(value));
  }
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
}

TEST_F(TreeUnitTestSuite, DeleteTreeTest4) {
  bialger::BinarySearchTree<int32_t, int32_t&, std::less<>, std::equal_to<>, std::allocator<int32_t>> bst{};
  size_t size = 1000;
  std::vector<int32_t> values = GetRandomNumbers(size);

  for (int32_t& value : values) {
    bst.Insert(value, value);
  }

  std::reverse(values.begin(), values.end());

  for (int32_t& value : values) {
    bst.Delete(bst.FindFirst(value));
  }
}

TEST_F(TreeUnitTestSuite, DeleteTreeTest5) {
  bialger::BinarySearchTree<int32_t, int32_t&, std::less<>, std::equal_to<>, std::allocator<int32_t>> bst{};
  size_t size = 10000;
  std::vector<int32_t> values = GetRandomNumbers(size);
  std::random_device dev;
  std::mt19937 rng(dev());

  for (int32_t& value : values) {
    bst.Insert(value, value);
  }

  std::shuffle(values.begin(), values.end(), rng);

  for (int32_t& value : values) {
    bst.Delete(bst.FindFirst(value));
  }
}
