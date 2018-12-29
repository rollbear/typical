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


#ifndef TYPICAL_COMPOSE_HPP
#define TYPICAL_COMPOSE_HPP

#include <typical/function_support.hpp>

namespace typical
{
template <typename ...>
struct compose;

template <>
struct compose<>
{
  using continuation = identity;
  template <typename C = continuation>
  struct to
  {
    using T = detail::to<C>;
    template <typename ... Ts>
    using result = typename T::template result<Ts...>;
  };
};

template <typename F, typename ... Fs>
struct compose<F, Fs...>
{
  using continuation = typename F::continuation;
  template <typename C = continuation>
  struct to
  {
    template <typename ... Ts>
    using result = typename compose<Fs...>::template to<typename F::template to<C>>::template result<Ts...>;
  };
};

}
#endif //TYPICAL_COMPOSE_HPP
