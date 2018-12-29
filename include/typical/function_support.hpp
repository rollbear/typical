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


#ifndef TYPICAL_FUNCTION_SUPPORT_HPP
#define TYPICAL_FUNCTION_SUPPORT_HPP

#include <typical/constant.hpp>

#include <utility>

namespace typical
{

namespace detail
{

template <typename T, typename = void>
struct has_continuation
{
  static constexpr bool value = false;
};

template <typename T>
struct has_continuation<T, std::void_t<typename T::continuation>>
{
  static constexpr bool value = true;
};

template <typename T, bool = has_continuation<T>::value>
struct to_
{
  using type = T;
};

template <typename T>
struct to_<T, true>
{
  using type = typename T::template to<typename T::continuation>;
};


template <typename T>
using to = typename to_<T>::type;

}

template<typename...>
struct list {};

template<template<typename ...> class C>
struct make {
  template<typename ... Ts>
  using result = C<Ts...>;
};

template <typename F, typename T>
using apply_one = typename F::template result<T>;

struct identity {
  template<typename T>
  using result = T;
};

template <template <typename ...> class T, typename ... Ts>
struct bind_front {
  template <typename ... Vs>
  struct helper {
    using type = T<Ts..., Vs...>;
  };
  template <typename ... Vs>
  using result = typename helper<Vs...>::type;
};

template<template <typename...> class T>
struct from_type {
  using continuation = identity;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;
    template<typename ... Vs>
    struct helper {
      using type = apply_one<TO, typename T<Vs...>::type>;
    };
    template<typename ... Vs>
    using result = typename helper<Vs...>::type;
  };
};

template <template <typename ...> class T>
struct from_value
{
  using continuation = identity;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;
    template<typename ... Vs>
    using result = apply_one<TO, constant<T<Vs...>::value>>;
  };
};

}

#endif //TYPICAL_FUNCTION_SUPPORT_HPP
