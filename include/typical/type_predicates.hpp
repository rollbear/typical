/*
 * typical - C++ template meta programming library
 *
 * Copyright Björn Fahller 2018
 *
 *  Use, modification and distribution is subject to the
 *  Boost Software License, Version 1.0. (See accompanying
 *  file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt)
 *
 * Project home: https://github.com/rollbear/typical
 */


#ifndef TYPICAL_TYPE_PREDICATES_HPP
#define TYPICAL_TYPE_PREDICATES_HPP

#include <typical/function_support.hpp>
#include <typical/application.hpp>

namespace typical {
using is_pointer = from_value<std::is_pointer>;
using is_reference = from_value<std::is_reference>;
using is_lvalue_reference = from_value<std::is_lvalue_reference>;
using is_rvalue_reference = from_value<std::is_rvalue_reference>;
using is_const = from_value<std::is_const>;
using is_volatile = from_value<std::is_volatile>;

template <typename T>
using is_same = from_type<bind_front<std::is_same, T>::template result>;

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

template<typename F>
struct negate {
  using continuation = identity;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;
    template<typename ...Ts>
    using result = typename TO::template result<constant<!apply_pack<F, Ts...>::value>>;
  };
};

}
#endif //TYPICAL_TYPE_PREDICATES_HPP
