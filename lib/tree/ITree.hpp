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

  [[nodiscard]] virtual ITreeNode* Insert(const T& key) = 0;
  [[nodiscard]] virtual ITreeNode* Delete(ITreeNode* node) = 0;
  [[nodiscard]] virtual ITreeNode* Find(const T& key) const = 0;
  [[nodiscard]] virtual bool Contains(const T& key) const  = 0;

  virtual void InOrder(const std::function<void(ITreeNode*)>& callback) = 0;
  virtual void PreOrder(const std::function<void(ITreeNode*)>& callback) = 0;
  virtual void PostOrder(const std::function<void(ITreeNode*)>& callback) = 0;

  virtual void InOrder(const std::function<void(const ITreeNode*)>& callback) const = 0;
  virtual void PreOrder(const std::function<void(const ITreeNode*)>& callback) const = 0;
  virtual void PostOrder(const std::function<void(const ITreeNode*)>& callback) const = 0;


  [[nodiscard]] virtual const ITreeNode* GetRoot() const = 0;
  [[nodiscard]] virtual const ITreeNode* GetEnd() const = 0;
};

} // bialger

#endif //LIB_TREE_ITREE_HPP_
