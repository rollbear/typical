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


#ifndef TYPICAL_FRONT_HPP
#define TYPICAL_FRONT_HPP

#include <typical/function_support.hpp>
#include <typical/utilities.hpp>

namespace typical
{
struct front {
  using continuation = identity;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;
    template<typename T>
    static apply_one<TO, T> func(detail::proxy<T> *, ...);

    template<typename ... Ts>
    using result = decltype(func(static_cast<detail::proxy<Ts> *>(nullptr)...));
  };
};



}
#endif //TYPICAL_FRONT_HPP
