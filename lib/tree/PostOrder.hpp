#ifndef LIB_TREE_POSTORDER_HPP_
#define LIB_TREE_POSTORDER_HPP_

#include "ITraversal.hpp"
#include "ITemplateTree.hpp"
#include "TreeNode.hpp"

namespace bialger {

class PostOrder : public ITraversal {
 public:
  PostOrder() = delete;

  explicit PostOrder(ITree& tree);

 private:
  ITree& tree_;
};

} // bialger

#endif //LIB_TREE_POSTORDER_HPP_
