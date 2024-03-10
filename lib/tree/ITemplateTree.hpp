#ifndef LIB_TREE_ITEMPLATETREE_HPP_
#define LIB_TREE_ITEMPLATETREE_HPP_

#include <functional>

#include "ITreeNode.hpp"
#include "ITree.hpp"

namespace bialger {

template <typename T, typename U>
class ITemplateTree : public ITree {
 public:
  virtual ~ITemplateTree() = default;

  virtual void Clear() = 0;

  virtual void Insert(const T& key, const U& value) = 0;
  virtual void Delete(ITreeNode* node) = 0;
  [[nodiscard]] virtual ITreeNode* FindFirst(const T& key) const = 0;
  [[nodiscard]] virtual bool Contains(const T& key) const  = 0;

  virtual void InOrder(const std::function<void(ITreeNode*)>& callback) = 0;
  virtual void PreOrder(const std::function<void(ITreeNode*)>& callback) = 0;
  virtual void PostOrder(const std::function<void(ITreeNode*)>& callback) = 0;

  virtual void InOrder(const std::function<void(const ITreeNode*)>& callback) const = 0;
  virtual void PreOrder(const std::function<void(const ITreeNode*)>& callback) const = 0;
  virtual void PostOrder(const std::function<void(const ITreeNode*)>& callback) const = 0;
};

} // bialger

#endif //LIB_TREE_ITEMPLATETREE_HPP_
