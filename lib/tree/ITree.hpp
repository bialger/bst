#ifndef LIB_TREE_ITREE_HPP_
#define LIB_TREE_ITREE_HPP_

#include "ITreeNode.hpp"

namespace bialger {

class ITree {
 public:
  virtual ~ITree() = default;

  [[nodiscard]] virtual ITreeNode* GetRoot() = 0;
  [[nodiscard]] virtual ITreeNode* GetEnd() = 0;
  [[nodiscard]] virtual const ITreeNode* GetRoot() const = 0;
  [[nodiscard]] virtual const ITreeNode* GetEnd() const = 0;
  [[nodiscard]] virtual bool AllowsDuplicates() const = 0;
};

} // bialger

#endif //LIB_TREE_ITREE_HPP_
