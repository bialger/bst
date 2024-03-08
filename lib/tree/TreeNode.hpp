#ifndef LIB_TREE_TREENODE_HPP_
#define LIB_TREE_TREENODE_HPP_

#include "ITreeNode.hpp"

namespace bialger {

template<typename T, typename U, typename Less, typename Equals, typename More>
class TreeNode : public ITreeNode {
 public:
  T key;
  U value;
  TreeNode<T, U, Less, Equals, More>* parent;
  TreeNode<T, U, Less, Equals, More>* left;
  TreeNode<T, U, Less, Equals, More>* right;

  TreeNode() = delete;
  TreeNode(const T& key, const U& value) : key(key), value(value), parent(nullptr), left(nullptr), right(nullptr) {};

  [[nodiscard]] bool IsLess(const ITreeNode* other) const override {
    const auto* other_ = static_cast<const TreeNode<T, U, Less, Equals, More>*>(other);
    return Less()(key, other_->key);
  }

  [[nodiscard]] bool IsLessOrEqual(const ITreeNode* other) const override {
    const auto* other_ = static_cast<const TreeNode<T, U, Less, Equals, More>*>(other);
    return Less()(key, other_->key) || Equals()(key, other_->key);
  }

  [[nodiscard]] bool IsEqual(const ITreeNode* other) const override {
    const auto* other_ = static_cast<const TreeNode<T, U, Less, Equals, More>*>(other);
    return Equals()(key, other_->key);
  }

  [[nodiscard]] bool IsMoreOrEqual(const ITreeNode* other) const override {
    const auto* other_ = static_cast<const TreeNode<T, U, Less, Equals, More>*>(other);
    return Equals()(key, other_->key) || More()(key, other_->key);
  }

  [[nodiscard]] bool IsMore(const ITreeNode* other) const override {
    const auto* other_ = static_cast<const TreeNode<T, U, Less, Equals, More>*>(other);
    return More()(key, other_->key);
  }

  [[nodiscard]] bool IsRoot() const override {
    return parent == nullptr;
  }

  [[nodiscard]] bool IsLeaf() const override {
    return left == nullptr && right == nullptr;
  }

  [[nodiscard]] bool HasLeft() const override {
    return left != nullptr;
  }

  [[nodiscard]] bool HasRight() const override {
    return right != nullptr;
  }

  [[nodiscard]] const ITreeNode* GetParent() const override {
    return parent;
  }

  [[nodiscard]] const ITreeNode* GetLeft() const override {
    return left;
  }

  [[nodiscard]] const ITreeNode* GetRight() const override {
    return right;
  }
};

} // bialger

#endif //LIB_TREE_TREENODE_HPP_
