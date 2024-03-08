#ifndef LIB_TREE_PREORDER_HPP_
#define LIB_TREE_PREORDER_HPP_

#include "ITraversal.hpp"
#include "ITree.hpp"
#include "TreeNode.hpp"

namespace bialger {

template <typename T>
class PreOrder : public ITraversal {
 public:
  PreOrder() = delete;

  explicit PreOrder(const ITree<T>& tree) : tree_(tree) {}

 private:
  const ITree<T>& tree_;
};

} // bialger

#endif //LIB_TREE_PREORDER_HPP_
