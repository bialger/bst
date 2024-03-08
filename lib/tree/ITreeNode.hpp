#ifndef LIB_TREE_BASETREENODE_HPP_
#define LIB_TREE_BASETREENODE_HPP_

namespace bialger {

class ITreeNode {
 public:
  virtual ~ITreeNode() = default;

  virtual bool IsLess(const ITreeNode* other) const = 0;
  virtual bool IsLessOrEqual(const ITreeNode* other) const = 0;
  virtual bool IsEqual(const ITreeNode* other) const = 0;
  virtual bool IsMoreOrEqual(const ITreeNode* other) const = 0;
  virtual bool IsMore(const ITreeNode* other) const = 0;

  virtual bool IsRoot() const = 0;
  virtual bool IsLeaf() const = 0;
  virtual bool HasLeft() const = 0;
  virtual bool HasRight() const = 0;
};

} // bialger

#endif //LIB_TREE_BASETREENODE_HPP_
