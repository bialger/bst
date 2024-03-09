#ifndef LIB_TREE_BINARYSEARCHTREE_HPP_
#define LIB_TREE_BINARYSEARCHTREE_HPP_

#include "ITemplateTree.hpp"
#include "TreeNode.hpp"

namespace bialger {

template<typename T, typename U, typename Less, typename Equals, typename More, typename Allocator>
class BinarySearchTree : public ITemplateTree<T, U> {
 public:
  explicit BinarySearchTree(bool allow_duplicates = false)
      : end_(nullptr), root_(end_), allocator_(), allow_duplicates_(allow_duplicates) {};

  BinarySearchTree(const BinarySearchTree& other)
      : end_(nullptr), root_(end_), allocator_(), allow_duplicates_(other.allow_duplicates_) {
    other.PreOrder([&](const ITreeNode* current) {
      const auto* current_ = static_cast<const NodeType*>(current);
      this->Insert(current_->key, current_->value);
    });
  }

  BinarySearchTree<T, U, Less, Equals, More, Allocator>& operator=(const BinarySearchTree<T,
                                                                                          U,
                                                                                          Less,
                                                                                          Equals,
                                                                                          More,
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
      const auto* current_ = static_cast<const NodeType*>(current);
      this->allocator_.deallocate(current_, 1);
    });

    end_ = nullptr;
    root_ = end_;
  }

  [[nodiscard]] virtual ITreeNode* Insert(const T& key, const U& value) {

  }

  virtual void Delete(ITreeNode* node) {
    // TODO: implement
    // TODO: implement
  }

  [[nodiscard]] ITreeNode* Find(const T& key) const override {
    // TODO: implement
    // TODO: implement
  }

  [[nodiscard]] bool Contains(const T& key) const override {
    // TODO: implement
    // TODO: implement
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
  using NodeType = TreeNode<T, U, Less, Equals, More>;
  using AllocatorType = Allocator::template rebind<NodeType>::other;

  bool allow_duplicates_;
  NodeType* end_;
  NodeType* root_;
  AllocatorType allocator_;

  NodeType* CreateNode(const T& key, const U& value) {
    NodeType* new_node = allocator_.allocate(1);
    allocator_.construct(new_node, key, value);

    return new_node;
  }

  NodeType* Insert(NodeType* node, const T& key, const U& value) {
    if (node == nullptr) {
      NodeType* new_node = CreateNode(key, value);

      if (root_ == nullptr) {
        root_ = new_node;
      }

      return new_node;
    }

    if (Less()(key, node->key) || (allow_duplicates_ && Equals()(key, node->key))) {
      node->left = Insert(node->left, key, value);
    } else if (Equals()(key, node->key) && !allow_duplicates_) {
      node->value = value;
    } else {
      node->right = Insert(node->right, key, value);
    }

    return node;
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

  void InOrder(const NodeType* node,
               const std::function<void(const ITreeNode*)>& callback) const {
    if (node == nullptr) {
      return;
    }

    InOrder(node->left, callback);
    callback(node);
    InOrder(node->right, callback);
  }

  void PreOrder(const NodeType* node,
                const std::function<void(const ITreeNode*)>& callback) const {
    if (node == nullptr) {
      return;
    }

    callback(node);
    PreOrder(node->left, callback);
    PreOrder(node->right, callback);
  }

  void PostOrder(const NodeType* node,
                 const std::function<void(const ITreeNode*)>& callback) const {
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
