#ifndef TREE_SFINAE_HPP_
#define TREE_SFINAE_HPP_

#include <type_traits>

namespace bialger {

template<typename X, typename Enabled = void>
class comparator_transparent final : public ::std::false_type {};

template<typename X>
class comparator_transparent<X, ::std::void_t<typename X::is_transparent>> final
: public ::std::true_type {
};

template<typename Compare, typename T, typename K>
class are_comparable {
  template<typename C, typename D>
  static std::true_type test(decltype(Compare()(std::declval<C>(), std::declval<D>()))*);

  template<typename C, typename D>
  static std::false_type test(...);

 public:
  enum { value = decltype(test<T, K>(0))::value };
};

} // bialger

#endif //TREE_SFINAE_HPP_
