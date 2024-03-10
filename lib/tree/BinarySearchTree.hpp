#ifndef LIB_TREE_BINARYSEARCHTREE_HPP_
#define LIB_TREE_BINARYSEARCHTREE_HPP_

#include <memory>

#include "ITemplateTree.hpp"
#include "TreeNode.hpp"

namespace bialger {

template<typename T, typename U, typename Less, typename Equals, typename Allocator>
class BinarySearchTree : public ITemplateTree<T, U> {
 public:
  using NodeType = TreeNode<T, U, Less, Equals>;
  using KeyType = T;
  using ValueType = U;

  explicit BinarySearchTree(bool allow_duplicates = false)
      : end_(nullptr), root_(nullptr), allocator_(), allow_duplicates_(allow_duplicates) {};

  BinarySearchTree(const BinarySearchTree& other)
      : end_(nullptr), root_(nullptr), allocator_(), allow_duplicates_(other.allow_duplicates_) {
    other.PreOrder([&](const ITreeNode* current) {
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
    other.PreOrder([&](const ITreeNode* current) {
      const auto* current_ = static_cast<const NodeType*>(current);
      this->Insert(current_->key, current_->value);
    });

    return *this;
  }

  ~BinarySearchTree() {
    Clear();
  }

  void Clear() override {
    PostOrder([&](ITreeNode* current) {
      auto* current_ = static_cast<NodeType*>(current);
      DeleteNode(current_);
    });

    end_ = nullptr;
    root_ = end_;
  }

  void Insert(const T& key, const U& value) override {
    root_ = Insert(root_, key, value);
  }

  void Delete(ITreeNode* node) override {
    if (node == nullptr) {
      return;
    }

    auto* node_ = static_cast<NodeType*>(node);
    Delete(node_);
//    NodeType* parent = node_->parent;
//
//    if (node_ == root_) {
//      root_ = Delete(node_);
//    } else if (node_ == parent->left) {
//      parent->left = Delete(node_);
//    } else {
//      parent->right = Delete(node_);
//    }
  }

  [[nodiscard]] ITreeNode* FindFirst(const T& key) const override {
    return FindFirst(root_, key);
  }

  [[nodiscard]] bool Contains(const T& key) const override {
    return FindFirst(key) != nullptr;
  }

  void InOrder(const std::function<void(const ITreeNode*)>& callback) const override {
    InOrder(root_, callback);
  }

  void PreOrder(const std::function<void(const ITreeNode*)>& callback) const override {
    PreOrder(root_, callback);
  }

  void PostOrder(const std::function<void(const ITreeNode*)>& callback) const override {
    PostOrder(root_, callback);
  }

  void InOrder(const std::function<void(ITreeNode*)>& callback) override {
    InOrder(root_, callback);
  }

  void PreOrder(const std::function<void(ITreeNode*)>& callback) override {
    PreOrder(root_, callback);
  }

  void PostOrder(const std::function<void(ITreeNode*)>& callback) override {
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

 protected:
  using NodeAllocatorType = typename std::allocator_traits<Allocator>::template rebind_alloc<NodeType>;
  using NodeAllocatorTraits = std::allocator_traits<NodeAllocatorType>;

  bool allow_duplicates_;
  NodeType* end_;
  NodeType* root_;
  NodeAllocatorType allocator_;

  NodeType* CreateNode(const T& key, const U& value) {
    NodeType* new_node = NodeAllocatorTraits::allocate(allocator_, 1);
    NodeAllocatorTraits::construct(allocator_, new_node, key, value);

    return new_node;
  }

  void DeleteNode(NodeType* node) {
    NodeAllocatorTraits::deallocate(allocator_, node, 1);
  }

  virtual NodeType* Insert(NodeType* node, const T& key, const U& value) {
    if (node == nullptr) {
      NodeType* new_node = CreateNode(key, value);

      return new_node;
    }

    if (Less()(key, node->key) || (allow_duplicates_ && Equals()(key, node->key))) {
      node->left = Insert(node->left, key, value);
      node->left->parent = node;
    } else if (Equals()(key, node->key) && !allow_duplicates_) {
      node->value = value;
    } else if (Less()(node->key, key)) {
      node->right = Insert(node->right, key, value);
      node->right->parent = node;
    }

    return node;
  }

  virtual void Delete(NodeType* node) {
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

  NodeType* FindFirst(NodeType* node, const T& key) const {
    if (node == nullptr) {
      return nullptr;
    }

    if (Less()(key, node->key)) {
      return FindFirst(node->left, key);
    } else if (Less()(node->key, key)) {
      return FindFirst(node->right, key);
    }

    return node;
  }

  void SwapNodes(NodeType* first, NodeType* second) {
    if (first == nullptr || second == nullptr || first == second) {
      return;
    }

    NodeType* first_parent = first->parent;
    NodeType* first_left = first->left;
    NodeType* first_right = first->right;
    NodeType* second_parent = second->parent;
    NodeType* second_left = second->left;
    NodeType* second_right = second->right;

    bool first_left_son = !first->IsRoot() && (first == first->parent->left);
    bool second_left_son = !second->IsRoot() && (second == second->parent->left);

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

  void InOrder(NodeType* node, const std::function<void(ITreeNode*)>& callback) {
    if (node == nullptr) {
      return;
    }

    InOrder(node->left, callback);
    callback(node);
    InOrder(node->right, callback);
  }

  void PreOrder(NodeType* node, const std::function<void(ITreeNode*)>& callback) {
    if (node == nullptr) {
      return;
    }

    callback(node);
    PreOrder(node->left, callback);
    PreOrder(node->right, callback);
  }

  void PostOrder(NodeType* node, const std::function<void(ITreeNode*)>& callback) {
    if (node == nullptr) {
      return;
    }

    PostOrder(node->left, callback);
    PostOrder(node->right, callback);
    callback(node);
  }

  void InOrder(const NodeType* node, const std::function<void(const ITreeNode*)>& callback) const {
    if (node == nullptr) {
      return;
    }

    InOrder(node->left, callback);
    callback(node);
    InOrder(node->right, callback);
  }

  void PreOrder(const NodeType* node, const std::function<void(const ITreeNode*)>& callback) const {
    if (node == nullptr) {
      return;
    }

    callback(node);
    PreOrder(node->left, callback);
    PreOrder(node->right, callback);
  }

  void PostOrder(const NodeType* node, const std::function<void(const ITreeNode*)>& callback) const {
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
