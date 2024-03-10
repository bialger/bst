#include "PostOrder.hpp"

bialger::PostOrder::PostOrder(bialger::ITree& tree) : tree_(tree) {}

const bialger::ITreeNode* bialger::PostOrder::GetFirst() const {
  const ITreeNode* node = tree_.GetRoot();

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

const bialger::ITreeNode* bialger::PostOrder::GetLast() const {
  return tree_.GetRoot();
}

const bialger::ITreeNode* bialger::PostOrder::GetPredecessor(const bialger::ITreeNode* current) const {
  if (current == tree_.GetRoot()) {
    return tree_.GetEnd();
  } else if (current == tree_.GetEnd()) {
    return GetLast();
  }

  // If the given node has a left child, find the rightmost node in the left subtree
  if (current->HasLeft()) {
    const ITreeNode* node = current->GetLeft();

    while (node->HasRight()) {
      node = node->GetRight();
    }

    return node;
  }

  // If the given node does not have a left child, traverse up the tree to find the first ancestor
  // whose right child is also an ancestor of the given node
  const ITreeNode* node = current;
  while (!node->IsRoot() && node->GetParent()->GetLeft() == node) {
    node = node->GetParent();
  }

  return node->GetParent();
}

const bialger::ITreeNode* bialger::PostOrder::GetSuccessor(const bialger::ITreeNode* current) const {
  if (current == tree_.GetEnd()) {
    return tree_.GetRoot();
  }

  // If the given node has a right child, find the leftmost node in the right subtree
  if (current->HasRight()) {
    const ITreeNode* node = current->GetRight();

    while (node->HasLeft()) {
      node = node->GetLeft();
    }

    return node;
  }

  // If the given node does not have a right child, traverse up the tree to find the first ancestor
  // whose left child is also an ancestor of the given node
  const ITreeNode* node = current;
  while (!node->IsRoot() && node->GetParent()->GetRight() == node) {
    node = node->GetParent();
  }

  return node->GetParent();
}

bialger::ITreeNode* bialger::PostOrder::GetFirst() {
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

bialger::ITreeNode* bialger::PostOrder::GetLast() {
  return tree_.GetRoot();
}

bialger::ITreeNode* bialger::PostOrder::GetPredecessor(bialger::ITreeNode* current) {
  if (current == tree_.GetRoot()) {
    return tree_.GetEnd();
  } else if (current == tree_.GetEnd()) {
    return GetLast();
  }

  // If the given node has a left child, find the rightmost node in the left subtree
  if (current->HasLeft()) {
    ITreeNode* node = current->GetLeft();

    while (node->HasRight()) {
      node = node->GetRight();
    }

    return node;
  }

  // If the given node does not have a left child, traverse up the tree to find the first ancestor
  // whose right child is also an ancestor of the given node
  ITreeNode* node = current;
  while (!node->IsRoot() && node->GetParent()->GetLeft() == node) {
    node = node->GetParent();
  }

  return node->GetParent();
}

bialger::ITreeNode* bialger::PostOrder::GetSuccessor(bialger::ITreeNode* current) {
  if (current == tree_.GetEnd()) {
    return tree_.GetRoot();
  }

  // If the given node has a right child, find the leftmost node in the right subtree
  if (current->HasRight()) {
    ITreeNode* node = current->GetRight();

    while (node->HasLeft()) {
      node = node->GetLeft();
    }

    return node;
  }

  // If the given node does not have a right child, traverse up the tree to find the first ancestor
  // whose left child is also an ancestor of the given node
  ITreeNode* node = current;
  while (!node->IsRoot() && node->GetParent()->GetRight() == node) {
    node = node->GetParent();
  }

  return node->GetParent();
}
