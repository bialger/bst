#ifndef LIB_TREE_ITRAVERSAL_HPP_
#define LIB_TREE_ITRAVERSAL_HPP_

#include "ITreeNode.hpp"

namespace bialger {

class ITraversal {
 public:
  virtual ~ITraversal() = default;

  virtual const ITreeNode* GetFirst() = 0;
  virtual const ITreeNode* GetLast() = 0;
  virtual const ITreeNode* GetPredecessor(const ITreeNode* current) = 0;
  virtual const ITreeNode* GetSuccessor(const ITreeNode* current) = 0;
};

} // bialger

#endif //LIB_TREE_ITRAVERSAL_HPP_
