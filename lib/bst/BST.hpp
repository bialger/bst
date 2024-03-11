#ifndef LIB_BST_BST_HPP_
#define LIB_BST_BST_HPP_

#include "lib/tree/BinarySearchTree.hpp"
#include "lib/tree/InOrder.hpp"
#include "lib/tree/PreOrder.hpp"
#include "lib/tree/PostOrder.hpp"

#include "BstIterator.hpp"

namespace bialger {

template<typename T, typename Compare = std::less<>, typename Allocator = std::allocator<T>>
class BST {
 private:
  using TreeType = BinarySearchTree<T, T*, Compare, std::equal_to<>, Allocator>;
  using DefaultTraversal = InOrder;

 public:
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;
  using difference_type = ptrdiff_t;
  using iterator = BstIterator<T, BST>;
  using const_iterator = BstIterator<T, BST>;
  using reverse_iterator = BstIterator<T, BST, true>;
  using const_reverse_iterator = BstIterator<T, BST, true>;
  using key_type = T;
  using value_type = key_type;
  using key_compare = Compare;
  using value_compare = key_compare;
  using key_allocator = Allocator;
  using TreeInterface = ITemplateTree<typename TreeType::key_type, typename TreeType::value_type>;

 private:

};

} // bialger

#endif //LIB_BST_BST_HPP_
