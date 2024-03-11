#include "PreOrder.hpp"

bialger::PreOrder::PreOrder(const bialger::ITree& tree) : tree_(tree) {}

bialger::ITreeNode* bialger::PreOrder::GetFirst() const {
  return tree_.GetRoot();
}

bialger::ITreeNode* bialger::PreOrder::GetLast() const {
  ITreeNode* node = tree_.GetRoot();

  if (node == nullptr) {
    return node;
  }

  while (!node->IsLeaf()) {
    if (node->HasRight()) {
      node = node->GetRight();
    } else {
      node = node->GetLeft();
    }
  }

  return node;
}

bialger::ITreeNode* bialger::PreOrder::GetPredecessor(bialger::ITreeNode* current) const {
  if (current == GetFirst()) {
    return tree_.GetEnd();
  } else if (current == tree_.GetEnd()) {
    return GetLast();
  }

  ITreeNode* parent = current->GetParent();

  if (current == parent->GetRight() && parent->HasLeft()) {
    current = parent->GetLeft();

    while (!current->IsLeaf()) {
      if (current->HasRight()) {
        current = current->GetRight();
      } else {
        current = current->GetLeft();
      }
    }

    return current;
  }

  return parent;
}

bialger::ITreeNode* bialger::PreOrder::GetSuccessor(bialger::ITreeNode* current) const {
  if (current == tree_.GetEnd()) {
    return GetFirst();
  } else if (current == GetLast()) {
    return tree_.GetEnd();
  }

  if (current->HasLeft()) {
    return current->GetLeft();
  }

  if (current->HasRight()) {
    return current->GetRight();
  }

  ITreeNode* parent = current->GetParent();

  while (parent != nullptr) {
    if (parent->HasRight() && current == parent->GetLeft()) {
      return parent->GetRight();
    }

    current = parent;
    parent = current->GetParent();
  }

  return tree_.GetEnd();
}
