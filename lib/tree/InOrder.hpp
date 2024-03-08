#ifndef LIB_TREE_INORDER_HPP_
#define LIB_TREE_INORDER_HPP_

#include "ITraversal.hpp"
#include "ITree.hpp"
#include "TreeNode.hpp"

namespace bialger {

template <typename T>
class InOrder : public ITraversal {
 public:
  InOrder() = delete;

  explicit InOrder(const ITree<T>& tree) : tree_(tree) {};

  [[nodiscard]] const ITreeNode* GetFirst() const override {
    return GetMin(tree_.GetRoot());
  }

  [[nodiscard]] const ITreeNode* GetLast() const override {
    return GetMax(tree_.GetRoot());
  }

  [[nodiscard]] const ITreeNode* GetPredecessor(const ITreeNode* current) const override {
    if (current == tree_.GetRoot()) {
      return tree_.GetEnd();
    } else if (current == tree_.GetEnd()) {
      return GetLast();
    }

    if (current->HasLeft()) {
      return GetMax(current->GetLeft());
    }

    const ITreeNode* parent = current->GetParent();
    const ITreeNode* predecessor = current;

    while (parent != nullptr && predecessor == parent->GetLeft()) {
      predecessor = parent;
      parent = parent->GetParent();
    }

    return parent;
  }

  [[nodiscard]] const ITreeNode* GetSuccessor(const ITreeNode* current) const override {
    if (current == tree_.GetEnd()) {
      return tree_.GetRoot();
    }

    if (current->HasRight()) {
      return GetMin(current->GetRight());
    }

    const ITreeNode* parent = current->GetParent();
    const ITreeNode* successor = current;

    while (parent != nullptr && successor == parent->GetRight()) {
      successor = parent;
      parent = parent->GetParent();
    }

    return parent;
  }

  [[nodiscard]] ITreeNode* GetFirst() override {
    return GetMin(tree_.GetRoot());
  }

  [[nodiscard]] ITreeNode* GetLast() override {
    return GetMax(tree_.GetRoot());
  }

  [[nodiscard]] ITreeNode* GetPredecessor(ITreeNode* current) const override {
    if (current == tree_.GetRoot()) {
      return tree_.GetEnd();
    } else if (current == tree_.GetEnd()) {
      return GetLast();
    }

    if (current->HasLeft()) {
      return GetMax(current->GetLeft());
    }

    ITreeNode* parent = current->GetParent();
    ITreeNode* predecessor = current;

    while (parent != nullptr && predecessor == parent->GetLeft()) {
      predecessor = parent;
      parent = parent->GetParent();
    }

    return parent;
  }

  [[nodiscard]] ITreeNode* GetSuccessor(ITreeNode* current) const override {
    if (current == tree_.GetEnd()) {
      return tree_.GetRoot();
    }

    if (current->HasRight()) {
      return GetMin(current->GetRight());
    }

    ITreeNode* parent = current->GetParent();
    ITreeNode* successor = current;

    while (parent != nullptr && successor == parent->GetRight()) {
      successor = parent;
      parent = parent->GetParent();
    }

    return parent;
  }

 protected:
  const ITree<T>& tree_;

  [[nodiscard]] const ITreeNode* GetMin(const ITreeNode* current) const {
    while (current->HasLeft()) {
      current = current->GetLeft();
    }

    return current;
  }

  [[nodiscard]] const ITreeNode* GetMax(const ITreeNode* current) const {
    while (current->HasRight()) {
      current = current->GetRight();
    }

    return current;
  }

  [[nodiscard]] ITreeNode* GetMin(ITreeNode* current) {
    while (current->HasLeft()) {
      current = current->GetLeft();
    }

    return current;
  }

  [[nodiscard]] ITreeNode* GetMax(ITreeNode* current) {
    while (current->HasRight()) {
      current = current->GetRight();
    }

    return current;
  }
};

} // bialger

#endif //LIB_TREE_INORDER_HPP_
