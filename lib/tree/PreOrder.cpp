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
  if (current == GetFirst()) {
    return tree_.GetEnd();
  } else if (current == tree_.GetEnd()) {
    return GetLast();
  }

  // If the given node is the left child of its parent, the predecessor is the parent
  if (!current->IsRoot() && current->GetParent()->GetLeft() == current) {
    return current->GetParent();
  }

  if (current->HasLeft()) {
    const ITreeNode* node = current->GetLeft();

    while (node->HasRight()) {
      node = node->GetRight();
    }

    return node;
  }

  // Traverse upwards until finding the node that is the right child of its parent
  while (current != nullptr && !current->IsRoot() && current == current->GetParent()->GetLeft()) {
    current = current->GetParent();
  }

  // Return the predecessor node
  return current->GetParent();
}

const bialger::ITreeNode* bialger::PreOrder::GetSuccessor(const bialger::ITreeNode* current) const {
  if (current == tree_.GetEnd()) {
    return GetFirst();
  }

  // If the given node has a left child, the successor is the left child
  if (current->HasLeft()) {
    return current->GetLeft();
  }

  // If the given node has a right child, the successor is the right child
  if (current->HasRight()) {
    return current->GetRight();
  }

  // Traverse upwards until finding the node that is the left child of its parent
  while (current != nullptr && !current->IsRoot() && current == current->GetParent()->GetRight()) {
    current = current->GetParent();
  }

  // Return the successor node
  if (current != nullptr && !current->IsRoot()) {
    return current->GetParent()->GetRight();
  }

  return tree_.GetRoot();
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
  if (current == GetFirst()) {
    return tree_.GetEnd();
  } else if (current == tree_.GetEnd()) {
    return GetLast();
  }

  // If the given node is the left child of its parent, the predecessor is the parent
  if (!current->IsRoot() && current->GetParent()->GetLeft() == current) {
    return current->GetParent();
  }

  if (current->HasLeft()) {
    ITreeNode* node = current->GetLeft();

    while (node->HasRight()) {
      node = node->GetRight();
    }

    return node;
  }

  // Traverse upwards until finding the node that is the right child of its parent
  while (current != nullptr && !current->IsRoot() && current == current->GetParent()->GetLeft()) {
    current = current->GetParent();
  }

  // Return the predecessor node
  return current->GetParent();
}

bialger::ITreeNode* bialger::PreOrder::GetSuccessor(bialger::ITreeNode* current) {
  if (current == tree_.GetEnd()) {
    return GetFirst();
  }

  // If the given node has a left child, the successor is the left child
  if (current->HasLeft()) {
    return current->GetLeft();
  }

  // If the given node has a right child, the successor is the right child
  if (current->HasRight()) {
    return current->GetRight();
  }

  // Traverse upwards until finding the node that is the left child of its parent
  while (current != nullptr && !current->IsRoot() && current == current->GetParent()->GetRight()) {
    current = current->GetParent();
  }

  // Return the successor node
  if (current != nullptr && !current->IsRoot()) {
    return current->GetParent()->GetRight();
  }

  return tree_.GetRoot();
}
