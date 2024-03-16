#include "PostOrder.hpp"

bialger::PostOrder::PostOrder(const bialger::ITree& tree) : tree_(tree) {}

bialger::ITreeNode* bialger::PostOrder::GetFirst() const {
  ITreeNode* node = tree_.GetRoot();

  if (node == nullptr) {
    return node;
  }

  while (!node->IsLeaf()) {
    if (node->HasLeft()) {
      node = node->GetLeft();
    } else {
      node = node->GetRight();
    }
  }

  return node;
}

bialger::ITreeNode* bialger::PostOrder::GetLast() const {
  return tree_.GetRoot();
}

bialger::ITreeNode* bialger::PostOrder::GetEnd() const {
  return tree_.GetEnd();
}

bialger::ITreeNode* bialger::PostOrder::GetPredecessor(bialger::ITreeNode* current) const {
  if (current == GetFirst()) {
    return tree_.GetEnd();
  } else if (current == tree_.GetEnd()) {
    return GetLast();
  }

  if (current->HasRight()) {
    return current->GetRight();
  }

  if (current->HasLeft()) {
    return current->GetLeft();
  }

  ITreeNode* parent = current->GetParent();

  while (parent != nullptr) {
    if (parent->HasLeft() && current == parent->GetRight()) {
      return parent->GetLeft();
    }

    current = parent;
    parent = current->GetParent();
  }

  return tree_.GetEnd();
}

bialger::ITreeNode* bialger::PostOrder::GetSuccessor(bialger::ITreeNode* current) const {
  if (current == tree_.GetEnd()) {
    return GetFirst();
  } else if (current == GetLast()) {
    return tree_.GetEnd();
  }

  ITreeNode* parent = current->GetParent();

  if (parent != nullptr && parent->GetRight() == current) {
    return parent;
  }

  if (parent != nullptr && parent->GetLeft() == current) {
    if (parent->HasRight()) {
      current = parent->GetRight();

      while (!current->IsLeaf()) {
        if (current->HasLeft()) {
          current = current->GetLeft();
        } else {
          current = current->GetRight();
        }
      }

      return current;
    }

    return parent;
  }

  return tree_.GetEnd();
}
