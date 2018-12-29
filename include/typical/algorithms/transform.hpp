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


#ifndef TYPICAL_TRANSFORM_HPP
#define TYPICAL_TRANSFORM_HPP

#include <typical/function_support.hpp>
#include <typical/application.hpp>

namespace typical
{
template<typename F>
struct transform {
  using continuation = make<list>;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;
    template<typename ... Ts>
    using result = typename TO::template result<apply_pack<F, Ts>...>;
  };
};

}

#endif //TYPICAL_TRANSFORM_HPP
