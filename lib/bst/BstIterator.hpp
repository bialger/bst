#ifndef LIB_BST_BSTITERATOR_HPP_
#define LIB_BST_BSTITERATOR_HPP_

#include "lib/tree/BinarySearchTree.hpp"
#include "lib/tree/InOrder.hpp"
#include "lib/tree/PreOrder.hpp"
#include "lib/tree/PostOrder.hpp"
#include <set>

namespace bialger {

template<typename T, typename Compare, typename Allocator>
class BST;

template<typename T, typename Compare, typename Allocator, bool is_reversed = false>
class BstIterator {
 private:
  using NodeType = TreeNode<T, T*>;

 public:
  friend class BST<T, Compare, Allocator>;

  using iterator_category = std::bidirectional_iterator_tag;
  using difference_type = ptrdiff_t;
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using pointer = T*;
  using const_pointer = const T*;

  BstIterator() = delete;

  explicit BstIterator(const ITraversal& traversal) : traversal_(&traversal) {
    current_ = dynamic_cast<NodeType*>(is_reversed ? traversal_->GetLast() : traversal_->GetFirst());
  }

  BstIterator(ITreeNode* node, const ITraversal& traversal) : traversal_(&traversal) {
    current_ = dynamic_cast<NodeType*>(node);
  }

  BstIterator(const BstIterator& other) : current_(other.current_), traversal_(&other.traversal_) {}

  BstIterator& operator=(const BstIterator& other) {
    if (this == &other) {
      return *this;
    }

    if (traversal_ != other.traversal_) {
      throw std::invalid_argument("Can`t assign iterator with different traversals.");
    }

    current_ = other.current_;
    return *this;
  }

  const_reference operator*() const {
    return current_->key;
  }

  const_reference operator->() const {
    return current_->key;
  }

  BstIterator& operator++() {
    ITreeNode* next = is_reversed ? traversal_->GetPredecessor(current_) : traversal_->GetSuccessor(current_);
    current_ = dynamic_cast<NodeType*>(next);
    return *this;
  }

  [[nodiscard]] BstIterator operator++(int) {
    BstIterator tmp = *this;
    ++*this;
    return tmp;
  }

  BstIterator& operator--() {
    ITreeNode* next = is_reversed ? traversal_->GetSuccessor(current_) : traversal_->GetPredecessor(current_);
    current_ = dynamic_cast<NodeType*>(next);
    return *this;
  }

  [[nodiscard]] BstIterator operator--(int) {
    BstIterator tmp = *this;
    --*this;
    return tmp;
  }

  bool operator==(const BstIterator& other) {
    return current_ == other.current_ && traversal_ == other.traversal_;
  }

  bool operator!=(const BstIterator& other) {
    return !(*this == other);
  }

 private:
  NodeType* current_;
  const ITraversal* traversal_;
};

} // bialger

#endif //LIB_BST_BSTITERATOR_HPP_
