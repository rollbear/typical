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


#ifndef TYPICAL_FLATTEN_HPP
#define TYPICAL_FLATTEN_HPP

#include <typical/application.hpp>
#include <typical/algorithms/join.hpp>
#include <typical/function_support.hpp>

namespace typical
{
struct flatten
{
  using continuation = make<list>;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;
    template<typename T>
    struct helper;
    template<template<typename ...> class L, typename ... Ts>
    struct helper<L<Ts...>> {
      template<typename V>
      struct split {
        using type = apply_one<TO, V>;
      };
      template<typename ... Vs>
      struct split<L<Vs...>> {
        using type = apply_pack_to<join, TO, typename split<Vs>::type...>;
      };
      using type = apply_pack_to<join, TO, typename split<Ts>::type...>;
    };
    template<typename T>
    using result = typename helper<T>::type;
  };
};

}
#endif //TYPICAL_FLATTEN_HPP
