#include "InOrder.hpp"

const bialger::ITreeNode* bialger::InOrder::GetFirst() const {
  return GetMin(tree_.GetRoot());
}

const bialger::ITreeNode* bialger::InOrder::GetLast() const {
  return GetMax(tree_.GetRoot());
}

const bialger::ITreeNode* bialger::InOrder::GetPredecessor(const bialger::ITreeNode* current) const {
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

const bialger::ITreeNode* bialger::InOrder::GetSuccessor(const bialger::ITreeNode* current) const {
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

bialger::ITreeNode* bialger::InOrder::GetFirst() {
  return GetMin(tree_.GetRoot());
}

bialger::ITreeNode* bialger::InOrder::GetLast() {
  return GetMax(tree_.GetRoot());
}

bialger::ITreeNode* bialger::InOrder::GetPredecessor(bialger::ITreeNode* current) {
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

bialger::ITreeNode* bialger::InOrder::GetSuccessor(bialger::ITreeNode* current) {
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

const bialger::ITreeNode* bialger::InOrder::GetMin(const bialger::ITreeNode* current) {
  if (current == nullptr) {
    return current;
  }

  while (current->HasLeft()) {
    current = current->GetLeft();
  }

  return current;
}

const bialger::ITreeNode* bialger::InOrder::GetMax(const bialger::ITreeNode* current) {
  if (current == nullptr) {
    return current;
  }

  while (current->HasRight()) {
    current = current->GetRight();
  }

  return current;
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
