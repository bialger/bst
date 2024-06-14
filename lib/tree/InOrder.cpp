#include "InOrder.hpp"

bialger::InOrder::InOrder(const bialger::ITree& tree): tree_(tree) {}

bialger::ITreeNode* bialger::InOrder::GetFirst() const {
  return GetMin(tree_.GetRoot());
}

bialger::ITreeNode* bialger::InOrder::GetLast() const {
  return GetMax(tree_.GetRoot());
}

bialger::ITreeNode* bialger::InOrder::GetEnd() const {
  return tree_.GetEnd();
}

bialger::ITreeNode* bialger::InOrder::GetPredecessor(bialger::ITreeNode* current) const {
  if (current == GetFirst()) {
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

bialger::ITreeNode* bialger::InOrder::GetSuccessor(bialger::ITreeNode* current) const {
  if (current == tree_.GetEnd()) {
    return GetFirst();
  } else if (current == GetLast()) {
    return tree_.GetEnd();
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

bialger::ITreeNode* bialger::InOrder::GetMin(bialger::ITreeNode* current) {
  if (current == nullptr) {
    return current;
  }

  while (current->HasLeft()) {
    current = current->GetLeft();
  }

  return current;
}

bialger::ITreeNode* bialger::InOrder::GetMax(bialger::ITreeNode* current) {
  if (current == nullptr) {
    return current;
  }

  while (current->HasRight()) {
    current = current->GetRight();
  }

  return current;
}
