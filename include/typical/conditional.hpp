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


#ifndef TYPICAL_CONDITIONAL_HPP
#define TYPICAL_CONDITIONAL_HPP

namespace typical
{
template<bool>
struct conditional {
  template<typename T, typename>
  using result = T;
};

template<>
struct conditional<false> {
  template<typename, typename U>
  using result = U;
};

template<bool b, typename T, typename U>
using conditional_t = typename conditional<b>::template result<T, U>;

}

#endif //TYPICAL_CONDITIONAL_HPP
