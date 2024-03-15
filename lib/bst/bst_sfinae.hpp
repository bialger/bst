#ifndef BST_SFINAE_HPP_
#define BST_SFINAE_HPP_

#include <type_traits>
namespace bialger {

template<typename X, typename Enabled = void>
class is_iterator final : public ::std::false_type {};

template<typename X>
class is_iterator<X, ::std::void_t<typename X::iterator_category>> final
    : public ::std::true_type {
};

template<typename X, typename Enabled = void, typename EnabledSecond = void>
class is_iterable final : public ::std::false_type {};

template<typename X>
class is_iterable<X,
                  ::std::void_t<typename X::const_iterator>,
                  ::std::void_t<typename X::const_iterator::iterator_category>> final
    : public ::std::true_type {
};

template<typename X, typename Enabled = void>
class has_value_type final : public ::std::false_type {};

template<typename X>
class has_value_type<X, ::std::void_t<typename X::value_type>> final
    : public ::std::true_type {
};

} // bialger

#endif //BST_SFINAE_HPP_
