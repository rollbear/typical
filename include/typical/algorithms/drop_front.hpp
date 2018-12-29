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


#ifndef TYPICAL_DROP_FRONT_HPP
#define TYPICAL_DROP_FRONT_HPP

#include <typical/function_support.hpp>
#include <typical/utilities.hpp>
namespace typical
{

namespace detail {

template<template<typename ...> class, typename, typename>
struct make_n_;

template<template<typename ...> class C, typename T, std::size_t ... Is>
struct make_n_<C, T, std::index_sequence<Is...>> {
  template<std::size_t>
  using made = T;
  using type = C<made<Is>...>;
};

template<template<typename ...> class C, typename N, typename T>
using make_n = typename make_n_<C, T, std::make_index_sequence<N::value>>::type;
}
template <typename N>
struct drop_front
{
  using continuation = make<list>;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;

    template<typename>
    struct helper;

    template<typename ... Vs>
    struct helper<list<Vs...>> {
      template<typename ... Ts>
      static typename TO::template result<Ts...> func(Vs..., detail::proxy<Ts> *...);
    };

    template<typename ... Ts>
    using result = decltype(helper<detail::make_n<list, N, const void *>>::func(
      static_cast<detail::proxy<Ts> *>(nullptr)...));
  };
};

}
#endif //TYPICAL_DROP_FRONT_HPP
