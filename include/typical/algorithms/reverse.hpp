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


#ifndef TYPICAL_REVERSE_HPP
#define TYPICAL_REVERSE_HPP

#include <typical/function_support.hpp>
#include <typical/application.hpp>
#include <typical/algorithms/join.hpp>

// TODO: This naive implementation is super slow!

namespace typical
{
struct reverse {
  using continuation = make<list>;
  template<typename C = continuation>
  struct to {
    using TO = detail::to<C>;
    template<std::size_t N, typename, bool>
    struct helper;

    template<template<typename ...> class L, typename ... Ts>
    struct helper<0, L<Ts...>, false> {
      using type = L<Ts...>;
    };
    template<template<typename...> class L, typename T, typename ... Ts>
    struct helper<1, L<T, Ts...>, false> {
      using type = L<T, Ts...>;
    };
    template<template<typename ...> class L, typename T1, typename T2, typename ... Ts>
    struct helper<2, L<T1, T2, Ts...>, false> {
      using type = L<T2, T1, Ts...>;
    };
    template<template<typename ...> class L, typename T1, typename T2, typename T3, typename ... Ts>
    struct helper<3, L<T1, T2, T3, Ts...>, false> {
      using type = L<T3, T2, T1, Ts...>;
    };
    template<template<typename ...> class L, typename T1, typename T2, typename T3, typename T4, typename ... Ts>
    struct helper<4, L<T1, T2, T3, T4, Ts...>, false> {
      using type = L<T4, T3, T2, T1, Ts...>;
    };
    template<template<typename ...> class L, typename T1, typename T2, typename T3, typename T4, typename T5, typename ... Ts>
    struct helper<5, L<T1, T2, T3, T4, T5, Ts...>, false> {
      using type = L<T5, T4, T3, T2, T1, Ts...>;
    };
    template<template<typename ...> class L, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename ... Ts>
    struct helper<6, L<T1, T2, T3, T4, T5, T6, Ts...>, false> {
      using type = L<T6, T5, T4, T3, T2, T1, Ts...>;
    };
    template<template<typename ...> class L, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename ... Ts>
    struct helper<7, L<T1, T2, T3, T4, T5, T6, T7, Ts...>, false> {
      using type = L<T7, T6, T5, T4, T3, T2, T1, Ts...>;
    };
    template<template<typename ...> class L, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename ... Ts>
    struct helper<8, L<T1, T2, T3, T4, T5, T6, T7, T8, Ts...>, false> {
      using type = L<T8, T7, T6, T5, T4, T3, T2, T1, Ts...>;
    };
    template<template<typename ...> class L, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename ... Ts>
    struct helper<9, L<T1, T2, T3, T4, T5, T6, T7, T8, T9, Ts...>, false> {
      using type = L<T9, T8, T7, T6, T5, T4, T3, T2, T1, Ts...>;
    };
    template<std::size_t N, template<typename ...> class L, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename ... Ts>
    struct helper<N, L<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, Ts...>, true> {
      using type = apply_pack_to<join, TO, typename helper<
        N - 10, L<Ts...>, (N >= 20)>::type, L<T10, T9, T8, T7, T6, T5, T4, T3, T2, T1>>;
    };
    template<typename ...T>
    using result = typename helper<sizeof...(T), typename TO::template result<T...>, (sizeof...(T) >= 10)>::type;
  };
};

}
#endif //TYPICAL_REVERSE_HPP
