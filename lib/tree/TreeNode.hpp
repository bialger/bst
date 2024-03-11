#ifndef LIB_TREE_TREENODE_HPP_
#define LIB_TREE_TREENODE_HPP_

#include "ITreeNode.hpp"

namespace bialger {

template<typename T, typename U>
class TreeNode : public ITreeNode {
 public:
  using key_type = T;
  using value_type = U;

  T key;
  U value;
  TreeNode<T, U>* parent;
  TreeNode<T, U>* left;
  TreeNode<T, U>* right;

  TreeNode() = delete;
  TreeNode(const T& key, const U& value) : key(key), value(value), parent(nullptr), left(nullptr), right(nullptr) {};

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

  [[nodiscard]] ITreeNode* GetParent() override {
    return parent;
  }

  [[nodiscard]] ITreeNode* GetLeft() override {
    return left;
  }

  [[nodiscard]] ITreeNode* GetRight() override {
    return right;
  }
};

} // bialger

#endif //LIB_TREE_TREENODE_HPP_
