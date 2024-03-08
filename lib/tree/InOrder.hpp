#ifndef LIB_TREE_INORDER_HPP_
#define LIB_TREE_INORDER_HPP_

#include "ITraversal.hpp"
#include "ITree.hpp"
#include "TreeNode.hpp"

namespace bialger {

template <typename T>
class InOrder : public ITraversal {
 public:
  InOrder() = delete;

  explicit InOrder(const ITree<T>& tree) : tree_(tree) {};
 private:
  const ITree<T>& tree_;
};

} // bialger

#endif //LIB_TREE_INORDER_HPP_
