#ifndef LIB_BST_BST_HPP_
#define LIB_BST_BST_HPP_

#include <limits>

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
  using BstType = BST<T, Compare, Allocator>;

 public:
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;
  using difference_type = ptrdiff_t;
  using iterator = BstIterator<T, BstType>;
  using const_iterator = BstIterator<T, BstType>;
  using reverse_iterator = BstIterator<T, BstType, true>;
  using const_reverse_iterator = BstIterator<T, BstType, true>;
  using key_type = T;
  using value_type = key_type;
  using key_compare = Compare;
  using value_compare = key_compare;
  using key_allocator = Allocator;
  using TreeInterface = ITemplateTree<typename TreeType::key_type, typename TreeType::value_type>;

  template<typename U, typename Less = std::less<>, typename Alloc = std::allocator<T>>
  using Container = BST<U, Less, Alloc>;

  BST() : tree_(), pre_order_(tree_), in_order_(tree_), post_order_(tree_) {
    end_ = tree_.GetEnd();
  }

  BST(const BST& other) : tree_(other.tree_), pre_order_(tree_), in_order_(tree_), post_order_(tree_) {
    end_ = tree_.GetEnd();
  }

  BST& operator=(const BST& other) {
    if (this == &other) {
      return *this;
    }

    tree_ = other.tree_;
    end_ = tree_.GetEnd();
  }

  template<typename Traversal = DefaultTraversal>
  iterator begin() const {
    if constexpr (std::is_same<Traversal, PreOrder>::value) {
      return iterator(pre_order_);
    } else if (std::is_same<Traversal, PostOrder>::value) {
      return iterator(in_order_);
    } else if (std::is_same<Traversal, InOrder>::value) {
      return iterator(post_order_);
    } else {
      throw std::invalid_argument("Incorrect traversal type");
    }
  }

  template<typename Traversal = DefaultTraversal>
  iterator end() const {
    if constexpr (std::is_same<Traversal, PreOrder>::value) {
      return iterator(end_, pre_order_);
    } else if (std::is_same<Traversal, PostOrder>::value) {
      return iterator(end_, in_order_);
    } else if (std::is_same<Traversal, InOrder>::value) {
      return iterator(end_, post_order_);
    } else {
      throw std::invalid_argument("Incorrect traversal type");
    }
  }

  template<typename Traversal = DefaultTraversal>
  const_iterator cbegin() const {
    return begin<Traversal>();
  }

  template<typename Traversal = DefaultTraversal>
  const_iterator cend() const {
    return end<Traversal>();
  }

  template<typename Traversal = DefaultTraversal>
  reverse_iterator rbegin() const {
    if constexpr (std::is_same<Traversal, PreOrder>::value) {
      return reverse_iterator(pre_order_);
    } else if (std::is_same<Traversal, PostOrder>::value) {
      return reverse_iterator(in_order_);
    } else if (std::is_same<Traversal, InOrder>::value) {
      return reverse_iterator(post_order_);
    } else {
      throw std::invalid_argument("Incorrect traversal type");
    }
  }

  template<typename Traversal = DefaultTraversal>
  reverse_iterator rend() const {
    if constexpr (std::is_same<Traversal, PreOrder>::value) {
      return reverse_iterator(end_, pre_order_);
    } else if (std::is_same<Traversal, PostOrder>::value) {
      return reverse_iterator(end_, in_order_);
    } else if (std::is_same<Traversal, InOrder>::value) {
      return reverse_iterator(end_, post_order_);
    } else {
      throw std::invalid_argument("Incorrect traversal type");
    }
  }

  template<typename Traversal = DefaultTraversal>
  const_reverse_iterator crbegin() const {
    return rbegin<Traversal>();
  }

  template<typename Traversal = DefaultTraversal>
  const_reverse_iterator crend() const {
    return rend<Traversal>();
  }

  bool operator==(const BST& other) const {
    if (tree_.GetSize() != other.tree_.GetSize()) {
      return false;
    }

    for (const_iterator this_it = cbegin(), other_it = other.cbegin();
         this_it != cend() && other_it != cend();
         ++this_it, ++other_it) {
      if (*this_it != *other_it) {
        return false;
      }
    }

    return true;
  }

  bool operator!=(const BST& other) const {
    return !(*this == other);
  }

  void swap(BST& other) {
    std::swap(tree_, other.tree_);
  }

  size_type size() const {
    return tree_.GetSize();
  }

  static difference_type max_size() {
    return std::numeric_limits<difference_type>::max();
  }

 private:
  TreeType tree_;
  ITreeNode* end_;
  PreOrder pre_order_;
  InOrder in_order_;
  PostOrder post_order_;
};

template<typename T, typename Compare = std::less<>, typename Allocator = std::allocator<T>>
void swap(BST<T, Compare, Allocator>& first, BST<T, Compare, Allocator>& second) {
  first.swap(second);
}

} // bialger

#endif //LIB_BST_BST_HPP_
