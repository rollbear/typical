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


#ifndef TYPICAL_APPLICATION_HPP
#define TYPICAL_APPLICATION_HPP

#include <typical/function_support.hpp>
#include <typical/compose.hpp>

namespace typical
{
struct unwrap {
  using continuation = make<list>;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;
    template<typename T>
    struct helper {
      using type = typename TO::template result<T>;
    };
    template<template<typename ...> class L, typename... Ts>
    struct helper<L<Ts...>> {
      using type = typename TO::template result<Ts...>;
    };
    template<typename ...Ts>
    using result = typename helper<Ts...>::type;
  };
};

template <typename F, typename C, typename ... Ts>
using apply_pack_to = typename F::template to<C>::template result<Ts...>;
template <typename F, typename ... Ts>
using apply_pack = typename F::template to<typename F::continuation>::template result<Ts...>;

template <typename F, typename C, typename ... Ts>
using apply_list_to = apply_pack_to<compose<F, unwrap>, C, Ts...>;
template <typename F, typename ... Ts>
using apply_list = apply_pack<compose<F, unwrap>, Ts...>;


}

#endif //TYPICAL_APPLICATION_HPP
