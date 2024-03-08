#ifndef LIB_TREE_POSTORDER_HPP_
#define LIB_TREE_POSTORDER_HPP_

#include "ITraversal.hpp"
#include "ITree.hpp"
#include "TreeNode.hpp"

namespace bialger {

template <typename T>
class PostOrder : public ITraversal {
 public:
  PostOrder() = delete;

  explicit PostOrder(const ITree<T>& tree) : tree_(tree) {};

 private:
  const ITree<T>& tree_;
};

} // bialger

#endif //LIB_TREE_POSTORDER_HPP_
