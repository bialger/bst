#include "PreOrder.hpp"

bialger::PreOrder::PreOrder(bialger::ITree& tree) : tree_(tree) {}

const bialger::ITreeNode* bialger::PreOrder::GetFirst() const {
  return tree_.GetRoot();
}

const bialger::ITreeNode* bialger::PreOrder::GetLast() const {
  const ITreeNode* node = tree_.GetRoot();

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

const bialger::ITreeNode* bialger::PreOrder::GetPredecessor(const bialger::ITreeNode* current) const {
  const ITreeNode* root = tree_.GetRoot();

  if (current == tree_.GetRoot()) {
    return tree_.GetEnd();
  } else if (current == tree_.GetEnd()) {
    return GetLast();
  }

  if (current->HasLeft()) {
    const ITreeNode* node = current->GetLeft();

    while (node->HasRight()) {
      node = node->GetRight();
    }

    return node;
  }

  const ITreeNode* predecessor = nullptr;
  const ITreeNode* node = root;

  while (node != current) {
    if (current->IsMore(node)) {
      predecessor = node;
      node = node->GetRight();
    } else {
      node = node->GetLeft();
    }
  }

  return predecessor;
}

const bialger::ITreeNode* bialger::PreOrder::GetSuccessor(const bialger::ITreeNode* current) const {
  const ITreeNode* root = tree_.GetRoot();
  bool allows_duplicates = tree_.AllowsDuplicates();

  if (current == tree_.GetEnd()) {
    return tree_.GetRoot();
  }

  if (current->HasRight()) {
    const ITreeNode* node = current->GetRight();

    while (node->HasLeft()) {
      node = node->GetLeft();
    }

    return node;
  }

  const ITreeNode* successor = nullptr;
  const ITreeNode* node = root;

  while (node != current) {
    if (current->IsLess(node) || (allows_duplicates && current->IsEqual(node))) {
      successor = node;
      node = node->GetLeft();
    } else {
      node = node->GetRight();
    }
  }

  return successor;
}

bialger::ITreeNode* bialger::PreOrder::GetFirst() {
  return tree_.GetRoot();
}

bialger::ITreeNode* bialger::PreOrder::GetLast() {
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
bialger::ITreeNode* bialger::PreOrder::GetPredecessor(bialger::ITreeNode* current) {
  ITreeNode* root = tree_.GetRoot();

  if (current == tree_.GetRoot()) {
    return tree_.GetEnd();
  } else if (current == tree_.GetEnd()) {
    return GetLast();
  }

  if (current->HasLeft()) {
    ITreeNode* node = current->GetLeft();

    while (node->HasRight()) {
      node = node->GetRight();
    }

    return node;
  }

  ITreeNode* predecessor = nullptr;
  ITreeNode* node = root;

  while (node != current) {
    if (current->IsMore(node)) {
      predecessor = node;
      node = node->GetRight();
    } else {
      node = node->GetLeft();
    }
  }

  return predecessor;
}

bialger::ITreeNode* bialger::PreOrder::GetSuccessor(bialger::ITreeNode* current) {
  ITreeNode* root = tree_.GetRoot();
  bool allows_duplicates = tree_.AllowsDuplicates();

  if (current == tree_.GetEnd()) {
    return tree_.GetRoot();
  }

  if (current->HasRight()) {
    ITreeNode* node = current->GetRight();

    while (node->HasLeft()) {
      node = node->GetLeft();
    }

    return node;
  }

  ITreeNode* successor = nullptr;
  ITreeNode* node = root;

  while (node != current) {
    if (current->IsLess(node) || (allows_duplicates && current->IsEqual(node))) {
      successor = node;
      node = node->GetLeft();
    } else {
      node = node->GetRight();
    }
  }

  return successor;
}
