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


#ifndef TYPICAL_COUNT_IF_HPP
#define TYPICAL_COUNT_IF_HPP

#include <typical/function_support.hpp>
#include <typical/application.hpp>

namespace typical
{
template<typename P>
struct count_if {
  using continuation = identity;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;

    template<auto ... Is>
    static constexpr auto sum = (0 + ...  + Is);

    template<typename T>
    using eval = apply_pack<P, T>;
    template<typename ...Ts>
    using result = typename TO::template result<constant<sum<eval<Ts>::value...>>>;
  };
};

}
#endif //TYPICAL_COUNT_IF_HPP
