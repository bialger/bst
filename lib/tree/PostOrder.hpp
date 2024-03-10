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

  [[nodiscard]] const ITreeNode* GetFirst() const override;
  [[nodiscard]] const ITreeNode* GetLast() const override;
  [[nodiscard]] const ITreeNode* GetPredecessor(const ITreeNode* current) const override;
  [[nodiscard]] const ITreeNode* GetSuccessor(const ITreeNode* current) const override;

  [[nodiscard]] ITreeNode* GetFirst() override;
  [[nodiscard]] ITreeNode* GetLast() override;
  [[nodiscard]] ITreeNode* GetPredecessor(ITreeNode* current) override;
  [[nodiscard]] ITreeNode* GetSuccessor(ITreeNode* current) override;
 private:
  ITree& tree_;
};

} // bialger

#endif //LIB_TREE_POSTORDER_HPP_
