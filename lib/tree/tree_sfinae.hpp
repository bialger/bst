#ifndef TREE_SFINAE_HPP_
#define TREE_SFINAE_HPP_

#include <type_traits>

namespace bialger {

template<typename Compare, typename T>
concept Comparator = requires(Compare& comp, T& t, T& u) {
  { comp(t, u) } -> std::same_as<bool>;
};

template<typename K, typename T, typename Compare>
concept ComparableType = requires(Compare& comp, T& t, K& k) {
  typename Compare::is_transparent;
  { comp(k, t) } -> std::same_as<bool>;
  { comp(t, k) } -> std::same_as<bool>;
};

template<typename T>
concept Allocable = sizeof(T) != 0;

template<typename Allocator>
concept AllocatorType = requires(Allocator& alloc) {
  typename Allocator::value_type;
  { alloc.allocate(1) } -> std::same_as<typename Allocator::value_type*>;
  { alloc.deallocate(alloc.allocate(1), 1) } -> std::same_as<void>;
};

} // bialger

#endif //TREE_SFINAE_HPP_
