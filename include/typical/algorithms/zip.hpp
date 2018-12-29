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


#ifndef TYPICAL_ZIP_HPP
#define TYPICAL_ZIP_HPP

#include <typical/application.hpp>
#include <typical/function_support.hpp>

namespace typical
{
template<typename F>
struct zip {
  using continuation = make<list>;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;
    template<typename L1, typename L2>
    struct helper;
    template<template<typename ...> class L1, typename ... L1s,
      template<typename...> class L2, typename ... L2s>
    struct helper<L1<L1s...>, L2<L2s...>> {
      using type = typename TO::template result< apply_pack<F,L1s, L2s>...>;
    };
    template<typename L1, typename L2>
    using result = typename helper<L1, L2>::type;
  };
};

}
#endif //TYPICAL_ZIP_HPP
