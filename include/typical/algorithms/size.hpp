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


#ifndef TYPICAL_SIZE_HPP
#define TYPICAL_SIZE_HPP

#include <typical/constant.hpp>
#include <typical/function_support.hpp>

namespace typical
{
struct size {
  template<typename>
  struct helper;
  template<template<typename ...> class L, typename ... Ts>
  struct helper<L<Ts...>> {
    static constexpr std::size_t value = sizeof...(Ts);
  };
  using continuation = identity;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;
    template<typename T>
    using result = apply_one<C, constant<helper<T>::value>>;
  };
};

}
#endif //TYPICAL_SIZE_HPP
