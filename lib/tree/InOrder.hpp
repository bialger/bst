#ifndef LIB_TREE_INORDER_HPP_
#define LIB_TREE_INORDER_HPP_

#include "ITraversal.hpp"
#include "ITemplateTree.hpp"
#include "TreeNode.hpp"

namespace bialger {

class InOrder : public ITraversal {
 public:
  InOrder() = delete;

  explicit InOrder(ITree& tree) : tree_(tree) {};

  [[nodiscard]] const ITreeNode* GetFirst() const override;
  [[nodiscard]] const ITreeNode* GetLast() const override;
  [[nodiscard]] const ITreeNode* GetPredecessor(const ITreeNode* current) const override;
  [[nodiscard]] const ITreeNode* GetSuccessor(const ITreeNode* current) const override;

  [[nodiscard]] ITreeNode* GetFirst() override;
  [[nodiscard]] ITreeNode* GetLast() override;
  [[nodiscard]] ITreeNode* GetPredecessor(ITreeNode* current) override;
  [[nodiscard]] ITreeNode* GetSuccessor(ITreeNode* current) override;

 protected:
  ITree& tree_;

  [[nodiscard]] static const ITreeNode* GetMin(const ITreeNode* current);
  [[nodiscard]] static const ITreeNode* GetMax(const ITreeNode* current);

  [[nodiscard]] static ITreeNode* GetMin(ITreeNode* current);
  [[nodiscard]] static ITreeNode* GetMax(ITreeNode* current);
};

} // bialger

#endif //LIB_TREE_INORDER_HPP_
