#ifndef TYPICAL_TYPE_PREDICATES_HPP
#define TYPICAL_TYPE_PREDICATES_HPP

#include <typical/function_support.hpp>

namespace typical {
using is_pointer = from_value<std::is_pointer>;
using is_reference = from_value<std::is_reference>;
using is_lvalue_reference = from_value<std::is_lvalue_reference>;
using is_rvalue_reference = from_value<std::is_rvalue_reference>;
using is_const = from_value<std::is_const>;
using is_volatile = from_value<std::is_volatile>;

template <typename T>
using is_same = from_type<bind_front<std::is_same, T>::template result>;

struct is_empty
{
  template <typename>
  struct helper { static constexpr bool value = false;};
  template <template <typename...> class L>
  struct helper<L<>> { static constexpr bool value = true;};
  using continuation = identity;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;
    template<typename ... Vs>
    using result = typename TO::template result<constant<helper<Vs...>::value>>;
  };
};

namespace detail {
template<template<typename ...> class T, typename U>
struct is_template_t {
  using type = constant<false>;
};

template<template<typename ...> class T, typename ... Ts>
struct is_template_t<T, T<Ts...>> {
  using type = constant<true>;
};
}
template<template<typename ...> class T>
struct is_template {
  using continuation = identity;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;
    template<typename U>
    using result = typename TO::template result<typename detail::is_template_t<T, U>::type>;
  };
};

}
#endif //TYPICAL_TYPE_PREDICATES_HPP
