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


#ifndef TYPICAL_AT_HPP
#define TYPICAL_AT_HPP

#include <typical/application.hpp>
#include <typical/function_support.hpp>
#include <typical/algorithms/drop_front.hpp>
#include <typical/algorithms/front.hpp>

namespace typical
{
template <typename N>
struct at
{
  using continuation = identity;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;
    template<typename ...Ts>
    using result = apply_pack_to<compose<front, drop_front<N>>, TO, Ts...>;
  };
};
}
#endif //TYPICAL_AT_HPP
