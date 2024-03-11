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
 public:
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;
  using difference_type = ptrdiff_t;
  using iterator = BstIterator<T, Compare, Allocator>;
  using const_iterator = BstIterator<T, Compare, Allocator>;
  using reverse_iterator = BstIterator<T, Compare, Allocator, true>;
  using const_reverse_iterator = BstIterator<T, Compare, Allocator, true>;
  using key_type = T;
  using value_type = key_type;
  using key_compare = Compare;
  using value_compare = key_compare;
  using key_allocator = Allocator;

 private:
  using NodeType = iterator::NodeType;
  using TreeType = BinarySearchTree<typename NodeType::key_type,
                                    typename NodeType::value_type,
                                    Compare,
                                    std::equal_to<>,
                                    Allocator>;
  using DefaultTraversal = InOrder;

 public:
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
    return iterator(GetTraversalLink<Traversal>());
  }

  template<typename Traversal = DefaultTraversal>
  iterator end() const {
    return iterator(end_, GetTraversalLink<Traversal>());
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
    return reverse_iterator(GetTraversalLink<Traversal>());
  }

  template<typename Traversal = DefaultTraversal>
  reverse_iterator rend() const {
    return reverse_iterator(end_, GetTraversalLink<Traversal>());
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

  [[nodiscard]] size_type size() const {
    return tree_.GetSize();
  }

  static difference_type max_size() {
    return std::numeric_limits<difference_type>::max();
  }

  void swap(BST& other) {
    std::swap(tree_, other.tree_);
  }

 private:
  TreeType tree_;
  ITreeNode* end_;
  PreOrder pre_order_;
  InOrder in_order_;
  PostOrder post_order_;

  template<typename Traversal>
  ITraversal& GetTraversalLink() {
    if constexpr (std::is_same<Traversal, PreOrder>::value) {
      return pre_order_;
    } else if (std::is_same<Traversal, InOrder>::value) {
      return in_order_;
    } else if (std::is_same<Traversal, PostOrder>::value) {
      return post_order_;
    } else {
      throw std::invalid_argument("Incorrect traversal type");
    }
  }
};

template<typename T, typename Compare = std::less<>, typename Allocator = std::allocator<T>>
void swap(BST<T, Compare, Allocator>& first, BST<T, Compare, Allocator>& second) {
  first.swap(second);
}

} // bialger

#endif //LIB_BST_BST_HPP_
