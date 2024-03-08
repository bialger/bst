#ifndef LIB_TREE_ITREE_HPP_
#define LIB_TREE_ITREE_HPP_

#include <functional>

#include "ITreeNode.hpp"

namespace bialger {

template <typename T>
class ITree {
 public:
  virtual ~ITree() = default;

  virtual void Clear() = 0;

  virtual ITreeNode* Insert(const T& key) = 0;
  virtual ITreeNode* Delete(ITreeNode* node) = 0;
  virtual void Contains(const T& key) const  = 0;
  virtual ITreeNode* Find(const T& key) = 0;

  virtual void InOrder(std::function<void(ITreeNode*)>) = 0;
  virtual void PreOrder(std::function<void(ITreeNode*)>) = 0;
  virtual void PostOrder(std::function<void(ITreeNode*)>) = 0;

  [[nodiscard]] virtual const ITreeNode* GetRoot() const = 0;
  [[nodiscard]] virtual const ITreeNode* GetEnd() const = 0;
};

} // bialger

#endif //LIB_TREE_ITREE_HPP_
