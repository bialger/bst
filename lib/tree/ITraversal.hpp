#ifndef LIB_TREE_ITRAVERSAL_HPP_
#define LIB_TREE_ITRAVERSAL_HPP_

#include "ITreeNode.hpp"

namespace bialger {

class ITraversal {
 public:
  virtual ~ITraversal() = default;

  [[nodiscard]] virtual const ITreeNode* GetFirst() const = 0;
  [[nodiscard]] virtual const ITreeNode* GetLast() const = 0;
  [[nodiscard]] virtual const ITreeNode* GetPredecessor(const ITreeNode* current) const = 0;
  [[nodiscard]] virtual const ITreeNode* GetSuccessor(const ITreeNode* current) const = 0;

  [[nodiscard]] virtual ITreeNode* GetFirst() = 0;
  [[nodiscard]] virtual ITreeNode* GetLast() = 0;
  [[nodiscard]] virtual ITreeNode* GetPredecessor(ITreeNode* current) const = 0;
  [[nodiscard]] virtual ITreeNode* GetSuccessor(ITreeNode* current) const = 0;
};

} // bialger

#endif //LIB_TREE_ITRAVERSAL_HPP_
