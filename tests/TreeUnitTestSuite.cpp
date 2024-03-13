#include "TreeUnitTestSuite.hpp"
#include "test_functions.hpp"

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

void TreeUnitTestSuite::SetUp() {
  values_random = GetRandomNumbers(size);
  values_unique = std::vector<int32_t>(size);

  for (int32_t i = 0; i < distance * size; i += static_cast<int32_t>(distance)) {
    values_unique[i / distance] = i + std::abs(static_cast<int32_t>(values_random[i / distance] % distance));
  }
}

void TreeUnitTestSuite::TearDown() {
  Test::TearDown();
}
