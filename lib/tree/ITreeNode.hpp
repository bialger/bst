#ifndef LIB_TREE_BASETREENODE_HPP_
#define LIB_TREE_BASETREENODE_HPP_

namespace bialger {

class ITreeNode {
 public:
  virtual ~ITreeNode() = default;

  [[nodiscard]] virtual bool IsLess(const ITreeNode* other) const = 0;
  [[nodiscard]] virtual bool IsLessOrEqual(const ITreeNode* other) const = 0;
  [[nodiscard]] virtual bool IsEqual(const ITreeNode* other) const = 0;
  [[nodiscard]] virtual bool IsMoreOrEqual(const ITreeNode* other) const = 0;
  [[nodiscard]] virtual bool IsMore(const ITreeNode* other) const = 0;

  [[nodiscard]] virtual bool IsRoot() const = 0;
  [[nodiscard]] virtual bool IsLeaf() const = 0;
  [[nodiscard]] virtual bool HasLeft() const = 0;
  [[nodiscard]] virtual bool HasRight() const = 0;

  [[nodiscard]] virtual const ITreeNode* GetParent() const = 0;
  [[nodiscard]] virtual const ITreeNode* GetLeft() const = 0;
  [[nodiscard]] virtual const ITreeNode* GetRight() const = 0;

  [[nodiscard]] virtual ITreeNode* GetParent() = 0;
  [[nodiscard]] virtual ITreeNode* GetLeft() = 0;
  [[nodiscard]] virtual ITreeNode* GetRight() = 0;
};

} // bialger

#endif //LIB_TREE_BASETREENODE_HPP_
