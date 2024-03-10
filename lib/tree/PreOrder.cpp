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

  const ITreeNode* parent = current->GetParent();

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

const bialger::ITreeNode* bialger::PreOrder::GetSuccessor(const bialger::ITreeNode* current) const {
  if (current == tree_.GetEnd()) {
    return GetFirst();
  } else if (current == GetLast()) {
    return tree_.GetEnd();
  }

  // If the given node has a left child, the successor is the left child
  if (current->HasLeft()) {
    return current->GetLeft();
  }

  // If the given node has a right child, the successor is the right child
  if (current->HasRight()) {
    return current->GetRight();
  }

  const ITreeNode* parent = current->GetParent();

  // Traverse upwards until finding the node that is the left child of its parent
  while (parent != nullptr) {
    if (parent->HasRight() && current == parent->GetLeft()) {
      return parent->GetRight();
    }

    current = parent;
    parent = current->GetParent();
  }

  return tree_.GetEnd();
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

bialger::ITreeNode* bialger::PreOrder::GetSuccessor(bialger::ITreeNode* current) {
  if (current == tree_.GetEnd()) {
    return GetFirst();
  } else if (current == GetLast()) {
    return tree_.GetEnd();
  }

  // If the given node has a left child, the successor is the left child
  if (current->HasLeft()) {
    return current->GetLeft();
  }

  // If the given node has a right child, the successor is the right child
  if (current->HasRight()) {
    return current->GetRight();
  }

  ITreeNode* parent = current->GetParent();

  // Traverse upwards until finding the node that is the left child of its parent
  while (parent != nullptr) {
    if (parent->HasRight() && current == parent->GetLeft()) {
      return parent->GetRight();
    }

    current = parent;
    parent = current->GetParent();
  }

  return tree_.GetEnd();
}
