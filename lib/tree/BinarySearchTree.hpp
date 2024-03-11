#ifndef LIB_TREE_BINARYSEARCHTREE_HPP_
#define LIB_TREE_BINARYSEARCHTREE_HPP_

#include <memory>

#include "ITemplateTree.hpp"
#include "TreeNode.hpp"

namespace bialger {

template<typename T, typename U, typename Less, typename Equals, typename Allocator>
class BinarySearchTree : public ITemplateTree<T, U> {
 public:
  using NodeType = TreeNode<T, U>;
  using key_type = T;
  using value_type = U;

  explicit BinarySearchTree(bool allow_duplicates = false)
      : end_(nullptr), root_(nullptr), allocator_(), allow_duplicates_(allow_duplicates), size_{} {};

  BinarySearchTree(const BinarySearchTree& other)
      : end_(nullptr), root_(nullptr), allocator_(), allow_duplicates_(other.allow_duplicates_), size_{} {
    other.PreOrder([&](const NodeType* current) {
      const auto* current_ = static_cast<const NodeType*>(current);
      this->Insert(current_->key, current_->value);
    });
  }

  BinarySearchTree<T, U, Less, Equals, Allocator>& operator=(const BinarySearchTree<T,
                                                                                    U,
                                                                                    Less,
                                                                                    Equals,
                                                                                    Allocator>& other) {
    if (this == &other) {
      return *this;
    }

    Clear();
    other.PreOrder([&](const NodeType* current) {
      const auto* current_ = static_cast<const NodeType*>(current);
      this->Insert(current_->key, current_->value);
    });

    return *this;
  }

  ~BinarySearchTree() {
    Clear();
  }

  void Clear() override {
    PostOrder([&](NodeType* current) {
      auto* current_ = static_cast<NodeType*>(current);
      DeleteNode(current_);
    });

    end_ = nullptr;
    root_ = end_;
  }

  NodeType* Insert(const T& key, const U& value) override {
    NodeType* result_node = nullptr;
    root_ = Insert(root_, result_node, key, value);
    return result_node;
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

  [[nodiscard]] ITreeNode* GetRoot() override {
    return root_;
  }

  [[nodiscard]] ITreeNode* GetEnd() override {
    return end_;
  }

  [[nodiscard]] const ITreeNode* GetRoot() const override {
    return root_;
  }

  [[nodiscard]] const ITreeNode* GetEnd() const override {
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

  virtual NodeType* Insert(NodeType* node, NodeType*& result_node, const T& key, const U& value) {
    if (node == nullptr) {
      NodeType* new_node = CreateNode(key, value);
      result_node = new_node;

      return new_node;
    }

    if (Equals()(key, node->key) && !allow_duplicates_) {
      node->value = value;
    } else if ((Less()(key, node->key)) || (allow_duplicates_ && Equals()(key, node->key))) {
      node->left = Insert(node->left, result_node, key, value);
      node->left->parent = node;
    } else  if (Less()(node->key, key)) {
      node->right = Insert(node->right, result_node, key, value);
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

    if (Less()(key, node->key)) {
      return FindFirst(node->left, key);
    } else if (Less()(node->key, key)) {
      return FindFirst(node->right, key);
    }

    return node;
  }

  NodeType* FindNextByKey(NodeType* node, const T& key) const {
    NodeType* next = nullptr;

    while (node != nullptr) {
      if (Equals()(key, node->key) && !allow_duplicates_) {
        node = node->right;
      } else if (Less()(key, node->key) || (allow_duplicates_ && Equals()(key, node->key))) {
        if (next == nullptr || Less()(node->key, next->key)) {
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
