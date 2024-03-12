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
  using TreeType = BinarySearchTree<T,
                                    const T*,
                                    Compare,
                                    std::equal_to<>,
                                    Allocator>;
  using NodeType = TreeType::NodeType;
  using DefaultTraversal = InOrder;

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
  using TreeInterface = TreeType::TreeInterface;

  BST() : tree_(), pre_order_(tree_), in_order_(tree_), post_order_(tree_) {
    end_ = tree_.GetEnd();
  }

  BST(const BST& other) : tree_(other.tree_), pre_order_(tree_), in_order_(tree_), post_order_(tree_) {
    end_ = tree_.GetEnd();
  }

  BST(const std::initializer_list<T>& list) : tree_(), pre_order_(tree_), in_order_(tree_), post_order_(tree_) {
    end_ = tree_.GetEnd();
    auto it = list.cbegin();
    auto end = list.cend();

    for (; it != end; ++it) {
      insert(*it);
    }
  }

  template<typename InputIt,
      std::enable_if_t<
          std::is_same<InputIt, T*>::value || std::is_same<InputIt, const T*>::value
              || (is_iterator<InputIt>::value && has_value_type<InputIt>::value),
          bool> = true>
  BST(InputIt first, InputIt last) : tree_(), pre_order_(tree_), in_order_(tree_), post_order_(tree_) {
    end_ = tree_.GetEnd();

    for (; first != last; ++first) {
      insert(*first);
    }
  }

  BST& operator=(const BST& other) {
    if (this == &other) {
      return *this;
    }

    tree_ = other.tree_;
    end_ = tree_.GetEnd();
  }

  void clear() {
    tree_.Clear();
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

  template<typename Traversal = DefaultTraversal>
  std::pair<iterator, bool> insert(const T& key) {
    auto result = tree_.Insert(key, &key);
    iterator it = iterator(result.first, GetTraversalLink<Traversal>());
    return {it, result.second};
  }

  template<typename Traversal = DefaultTraversal>
  iterator insert(iterator pos, const T& key) {
    --pos;

    if (pos.current_ == tree_.GetEnd()) {
      ++pos;
    }

    auto result = tree_.InsertFromNode(pos.current_, key, &key);
    return iterator(result.first, GetTraversalLink<Traversal>());
  }

  template<typename InputIt,
      std::enable_if_t<
          std::is_same<InputIt, T*>::value || std::is_same<InputIt, const T*>::value
              || (is_iterator<InputIt>::value && has_value_type<InputIt>::value),
          bool> = true>
  void insert(InputIt first, InputIt last) {
    for (; first != last; ++first) {
      insert(*first);
    }
  }

  template<typename Container,
      std::enable_if_t<
          is_iterable<Container>::value && has_value_type<Container>::value,
          bool> = true>
  void insert(const Container& other) {
    auto it = other.cbegin();
    auto end = other.cend();

    for (; it != end; ++it) {
      insert(*it);
    }
  }

  void insert(const std::initializer_list<T>& list) {
    auto it = list.cbegin();
    auto end = list.cend();

    for (; it != end; ++it) {
      insert(*it);
    }
  }

  iterator erase(iterator pos) {
    auto next = pos.next();
    tree_.Delete();
    return next;
  }

  iterator erase(const_iterator first, const_iterator last) {
    for (; first != last; ++first) {
      Delete(first.current_);
    }

    return last;
  }

  size_type erase(const T& key) {
    size_type counter = 0;

    for (auto it = find(key); it != end(); it = find(key)) {
      erase(it);
      ++counter;
    }

    return counter;
  }

  template<typename Traversal = DefaultTraversal>
  iterator find(const T& key) {
    return iterator(tree_.FindFirst(key), GetTraversalLink<Traversal>());
  }

  template<typename Traversal = DefaultTraversal>
  const_iterator find(const T& key) const {
    return iterator(tree_.FindFirst(key), GetTraversalLink<Traversal>());
  }

  size_type count(const T& key) const {
    return (find(key) == cend()) ? 0 : 1;
  }

  bool contains(const T& key) const {
    return find(key) != cend();
  }

  iterator lower_bound(const T& key) {
    NodeType* first = tree_.FindFirst(key);
    const ITraversal& traversal = in_order_;

    if (first == end_) {
      return iterator(tree_.FindNext(key), traversal);
    }

    return iterator(first, traversal);
  }

  const_iterator lower_bound(const T& key) const {
    NodeType* first = tree_.FindFirst(key);
    const ITraversal& traversal = in_order_;

    if (first == end_) {
      return iterator(tree_.FindNext(key), traversal);
    }

    return iterator(first, traversal);
  }

  iterator upper_bound(const T& key) {
    return iterator(tree_.FindNext(key), in_order_);
  }

  const_iterator upper_bound(const T& key) const {
    return const_iterator(tree_.FindNext(key), in_order_);
  }

  std::pair<iterator, iterator> equal_range(const T& key) {
    NodeType* first = tree_.FindFirst(key);
    NodeType* next = tree_.FindNext(key);
    const ITraversal& traversal = in_order_;

    if (first == end_) {
      return {iterator(next, traversal), iterator(next, traversal)};
    }

    return {iterator(first, traversal), iterator(next, traversal)};
  }

  std::pair<const_iterator, const_iterator> equal_range(const T& key) const {
    NodeType* first = tree_.FindFirst(key);
    NodeType* next = tree_.FindNext(key);
    const ITraversal& traversal = in_order_;

    if (first == end_) {
      return {const_iterator(next, traversal), const_iterator(next, traversal)};
    }

    return {const_iterator(first, traversal), const_iterator(next, traversal)};
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

  auto operator<=>(const BST& other) const {
    if (tree_.GetSize() < other.tree_.GetSize()) {
      return std::strong_ordering::less;
    } else if (tree_.GetSize() > other.tree_.GetSize()) {
      return std::strong_ordering::greater;
    }

    for (const_iterator this_it = cbegin(), other_it = other.cbegin();
         this_it != cend() && other_it != cend();
         ++this_it, ++other_it) {
      if (*this_it < *other_it) {
        return std::strong_ordering::less;
      } else if (*this_it > *other_it) {
        return std::strong_ordering::greater;
      }
    }

    return std::strong_ordering::equivalent;
  }

  [[nodiscard]] size_type size() const {
    return tree_.GetSize();
  }

  [[nodiscard]] bool empty() const {
    return tree_.GetSize() == 0;
  }

  static difference_type max_size() {
    return std::numeric_limits<difference_type>::max();
  }

  void swap(BST& other) {
    std::swap(tree_, other.tree_);
  }

  Allocator get_allocator() const {
    return Allocator();
  }

 private:
  TreeType tree_;
  ITreeNode* end_;
  PreOrder pre_order_;
  InOrder in_order_;
  PostOrder post_order_;

  template<typename Traversal>
  [[nodiscard]] const ITraversal& GetTraversalLink() const {
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

using CharSet = BST<char>;

} // bialger

#endif //LIB_BST_BST_HPP_
