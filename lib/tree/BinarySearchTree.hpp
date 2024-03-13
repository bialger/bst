#ifndef LIB_TREE_BINARYSEARCHTREE_HPP_
#define LIB_TREE_BINARYSEARCHTREE_HPP_

#include <memory>
#include <cstdint>
#include <type_traits>

#include "ITemplateTree.hpp"
#include "TreeNode.hpp"

namespace bialger {

template<typename X, typename Enabled = void>
class comparator_transparent final : public ::std::false_type {};

template<typename X>
class comparator_transparent<X, ::std::void_t<typename X::is_transparent>> final
    : public ::std::true_type {
};

template<typename Compare, typename T, typename K>
class are_comparable {
  template<typename C, typename D>
  static std::true_type test(decltype(Compare()(std::declval<C>(), std::declval<D>()))*);

  template<typename C, typename D>
  static std::false_type test(...);

 public:
  enum { value = decltype(test<T, K>(0))::value };
};

template<typename T, typename U, typename Less, typename Equals, typename Allocator>
class BinarySearchTree : public ITemplateTree<T, U> {
 public:
  using TreeInterface = ITemplateTree<T, U>;
  using NodeType = TreeNode<T, U>;
  using key_type = T;
  using value_type = U;

  explicit BinarySearchTree(bool allow_duplicates = false, const Less& less = Less())
      : end_(nullptr), root_(nullptr), allocator_(), allow_duplicates_(allow_duplicates), less_(&less), size_{} {};

  BinarySearchTree(const BinarySearchTree& other)
      : end_(nullptr),
        root_(nullptr),
        allocator_(),
        allow_duplicates_(other.allow_duplicates_),
        less_(other.less_),
        size_{} {
    other.PreOrder([&](const NodeType* current) {
      this->Insert(current->key, current->value);
    });
  }

  BinarySearchTree& operator=(const BinarySearchTree& other) {
    if (this == &other) {
      return *this;
    }

    allow_duplicates_ = other.allow_duplicates_;
    less_ = other.less_;
    allocator_ = other.allocator_;

    Clear();
    other.PreOrder([&](const NodeType* current) {
      this->Insert(current->key, current->value);
    });

    return *this;
  }

  ~BinarySearchTree() {
    Clear();
  }

  void Clear() override {
    PostOrder([&](NodeType* current) {
      DeleteNode(current);
    });

    end_ = nullptr;
    root_ = end_;
  }

  std::pair<NodeType*, bool> Insert(const T& key, const U& value) override {
    std::pair<NodeType*, bool> result = {end_, false};
    root_ = Insert(root_, result, key, value);
    return result;
  }

  void Delete(NodeType* node) override {
    if (node == nullptr || node == end_) {
      return;
    }

    if (node->HasLeft() && node->HasRight()) {
      NodeType* min = GetMin(node->right);
      SwapNodes(node, min);
      Delete(node);
    } else if (node->HasLeft()) {
      NodeType* left = node->left;
      NodeType* parent = node->parent;

      if (node == root_) {
        root_ = left;
        left->parent = nullptr;
      } else if (parent->left == node) {
        parent->left = left;
        left->parent = parent;
      } else {
        parent->right = left;
        left->parent = parent;
      }

      DeleteNode(node);
    } else if (node->HasRight()) {
      NodeType* right = node->right;
      NodeType* parent = node->parent;

      if (node == root_) {
        root_ = right;
        right->parent = nullptr;
      } else if (parent->left == node) {
        parent->left = right;
        right->parent = parent;
      } else {
        parent->right = right;
        right->parent = parent;
      }

      DeleteNode(node);
    } else {
      NodeType* parent = node->parent;

      if (node == root_) {
        root_ = end_;
      } else if (parent->left == node) {
        parent->left = nullptr;
      } else {
        parent->right = nullptr;
      }

      DeleteNode(node);
    }
  }

  [[nodiscard]] NodeType* FindFirst(const T& key) const override {
    return FindFirst(root_, key);
  }

  [[nodiscard]] NodeType* FindNext(const T& key) const override {
    return FindNextByKey(root_, key);
  }

  [[nodiscard]] bool Contains(const T& key) const override {
    return FindFirst(key) != nullptr;
  }

  template<typename K,
      std::enable_if_t<comparator_transparent<Less>::value
                           && are_comparable<Less, T, K>::value
                           && are_comparable<Equals, T, K>::value, bool> = true>
  [[nodiscard]] NodeType* FindFirst(const K& key) const {
    return FindFirst(root_, key);
  }

  template<typename K,
      std::enable_if_t<comparator_transparent<Less>::value
                           && are_comparable<Less, T, K>::value
                           && are_comparable<Equals, T, K>::value, bool> = true>
  [[nodiscard]] NodeType* FindNext(const K& key) const {
    return FindNextByKey(root_, key);
  }

  template<typename K,
      std::enable_if_t<comparator_transparent<Less>::value
                           && are_comparable<Less, T, K>::value
                           && are_comparable<Equals, T, K>::value, bool> = true>
  [[nodiscard]] bool Contains(const K& key) const {
    return FindFirst(key) != nullptr;
  }

  void InOrder(const std::function<void(const NodeType*)>& callback) const override {
    InOrder(root_, callback);
  }

  void PreOrder(const std::function<void(const NodeType*)>& callback) const override {
    PreOrder(root_, callback);
  }

  void PostOrder(const std::function<void(const NodeType*)>& callback) const override {
    PostOrder(root_, callback);
  }

  void InOrder(const std::function<void(NodeType*)>& callback) override {
    InOrder(root_, callback);
  }

  void PreOrder(const std::function<void(NodeType*)>& callback) override {
    PreOrder(root_, callback);
  }

  void PostOrder(const std::function<void(NodeType*)>& callback) override {
    PostOrder(root_, callback);
  }

  [[nodiscard]] ITreeNode* GetRoot() const override {
    return root_;
  }

  [[nodiscard]] ITreeNode* GetEnd() const override {
    return end_;
  }

  [[nodiscard]] bool AllowsDuplicates() const override {
    return allow_duplicates_;
  }

  [[nodiscard]] size_t GetSize() const override {
    return size_;
  }

 protected:
  using NodeAllocatorType = typename std::allocator_traits<Allocator>::template rebind_alloc<NodeType>;
  using NodeAllocatorTraits = std::allocator_traits<NodeAllocatorType>;

  bool allow_duplicates_;
  size_t size_;
  NodeType* end_;
  NodeType* root_;
  NodeAllocatorType allocator_;
  const Less* less_;

  NodeType* CreateNode(const T& key, const U& value) {
    NodeType* new_node = NodeAllocatorTraits::allocate(allocator_, 1);
    NodeAllocatorTraits::construct(allocator_, new_node, key, value);
    ++size_;

    return new_node;
  }

  void DeleteNode(NodeType* node) {
    NodeAllocatorTraits::deallocate(allocator_, node, 1);
    --size_;
  }

  virtual NodeType* Insert(NodeType* node, std::pair<NodeType*, bool>& result, const T& key, const U& value) {
    if (node == nullptr) {
      NodeType* new_node = CreateNode(key, value);
      result.first = new_node;
      result.second = true;

      return new_node;
    }

    if (Equals()(key, node->key) && !allow_duplicates_) {
      node->value = value;
      result.first = node;
      result.second = false;
    } else if (((*less_)(key, node->key)) || (allow_duplicates_ && Equals()(key, node->key))) {
      node->left = Insert(node->left, result, key, value);
      node->left->parent = node;
    } else if ((*less_)(node->key, key)) {
      node->right = Insert(node->right, result, key, value);
      node->right->parent = node;
    }

    return node;
  }

  NodeType* FindFirst(NodeType* node, const T& key) const {
    if (node == nullptr) {
      return nullptr;
    }

    if (Equals()(key, node->key)) {
      return node;
    }

    if ((*less_)(key, node->key)) {
      return FindFirst(node->left, key);
    } else if ((*less_)(node->key, key)) {
      return FindFirst(node->right, key);
    }

    return node;
  }

  template<typename K,
      std::enable_if_t<comparator_transparent<Less>::value
                           && are_comparable<Less, T, K>::value
                           && are_comparable<Equals, T, K>::value, bool> = true>
  NodeType* FindFirst(NodeType* node, const K& key) const {
    if (node == nullptr) {
      return nullptr;
    }

    if (Equals()(key, node->key)) {
      return node;
    }

    if ((*less_)(key, node->key)) {
      return FindFirst(node->left, key);
    } else if ((*less_)(node->key, key)) {
      return FindFirst(node->right, key);
    }

    return node;
  }

  NodeType* FindNextByKey(NodeType* node, const T& key) const {
    NodeType* next = nullptr;

    while (node != nullptr) {
      if (Equals()(key, node->key)) {
        node = node->right;
      } else if ((*less_)(key, node->key) || (allow_duplicates_ && Equals()(key, node->key))) {
        if (next == nullptr || (*less_)(node->key, next->key)) {
          next = node;
        }

        node = node->left;
      } else {
        node = node->right;
      }
    }

    return next;
  }

  template<typename K,
      std::enable_if_t<comparator_transparent<Less>::value
                           && are_comparable<Less, T, K>::value
                           && are_comparable<Equals, T, K>::value, bool> = true>
  NodeType* FindNextByKey(NodeType* node, const K& key) const {
    NodeType* next = nullptr;

    while (node != nullptr) {
      if (Equals()(key, node->key)) {
        node = node->right;
      } else if ((*less_)(key, node->key) || (allow_duplicates_ && Equals()(key, node->key))) {
        if (next == nullptr || (*less_)(node->key, next->key)) {
          next = node;
        }

        node = node->left;
      } else {
        node = node->right;
      }
    }

    return next;
  }

  void SwapNodes(NodeType* first, NodeType* second) {
    if (first == nullptr || second == nullptr || first == second) {
      return;
    }

    if (first->parent == nullptr) {
      root_ = second;
    } else if (first == first->parent->left) {
      first->parent->left = second;
    } else {
      first->parent->right = second;
    }

    if (second->parent == nullptr) {
      root_ = first;
    } else if (second == second->parent->left) {
      second->parent->left = first;
    } else {
      second->parent->right = first;
    }

    std::swap(first->left, second->left);
    std::swap(first->right, second->right);
    std::swap(first->parent, second->parent);

    if (first->HasLeft()) {
      first->left->parent = first;
    }

    if (first->HasRight()) {
      first->right->parent = first;
    }

    if (second->HasLeft()) {
      second->left->parent = second;
    }

    if (second->HasRight()) {
      second->right->parent = second;
    }
  }

  NodeType* GetMin(NodeType* current) {
    if (current == nullptr) {
      return current;
    }

    while (current->HasLeft()) {
      current = current->left;
    }

    return current;
  }

  NodeType* GetMax(NodeType* current) {
    if (current == nullptr) {
      return current;
    }

    while (current->HasRight()) {
      current = current->right;
    }

    return current;
  }

  void InOrder(NodeType* node, const std::function<void(NodeType*)>& callback) {
    if (node == nullptr) {
      return;
    }

    InOrder(node->left, callback);
    callback(node);
    InOrder(node->right, callback);
  }

  void PreOrder(NodeType* node, const std::function<void(NodeType*)>& callback) {
    if (node == nullptr) {
      return;
    }

    callback(node);
    PreOrder(node->left, callback);
    PreOrder(node->right, callback);
  }

  void PostOrder(NodeType* node, const std::function<void(NodeType*)>& callback) {
    if (node == nullptr) {
      return;
    }

    PostOrder(node->left, callback);
    PostOrder(node->right, callback);
    callback(node);
  }

  void InOrder(const NodeType* node, const std::function<void(const NodeType*)>& callback) const {
    if (node == nullptr) {
      return;
    }

    InOrder(node->left, callback);
    callback(node);
    InOrder(node->right, callback);
  }

  void PreOrder(const NodeType* node, const std::function<void(const NodeType*)>& callback) const {
    if (node == nullptr) {
      return;
    }

    callback(node);
    PreOrder(node->left, callback);
    PreOrder(node->right, callback);
  }

  void PostOrder(const NodeType* node, const std::function<void(const NodeType*)>& callback) const {
    if (node == nullptr) {
      return;
    }

    PostOrder(node->left, callback);
    PostOrder(node->right, callback);
    callback(node);
  }
};

} // bialger

#endif //LIB_TREE_BINARYSEARCHTREE_HPP_
