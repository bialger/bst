#ifndef LIB_TREE_PREORDER_HPP_
#define LIB_TREE_PREORDER_HPP_

#include "ITraversal.hpp"
#include "ITemplateTree.hpp"
#include "TreeNode.hpp"

namespace bialger {

class PreOrder : public ITraversal {
 public:
  PreOrder() = delete;

  explicit PreOrder(ITree& tree);

 private:
  ITree& tree_;
};

} // bialger

#endif //LIB_TREE_PREORDER_HPP_
