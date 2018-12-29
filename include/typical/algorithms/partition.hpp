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


#ifndef TYPICAL_PARTITION_HPP
#define TYPICAL_PARTITION_HPP

#include <typical/function_support.hpp>
#include <typical/application.hpp>
#include <typical/conditional.hpp>
#include <typical/algorithms/join.hpp>

namespace typical
{
template<typename P>
struct partition {
  using continuation = make<list>;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;
    template<typename ... Ts>
    struct helper {
      using type = typename TO::template result<apply_pack_to<join, make<list>, conditional_t<apply_pack<P, Ts>::value, list<Ts>, list<>>...>,
      apply_pack_to<join, make<list>, conditional_t<apply_pack<P, Ts>::value, list<>, list<Ts>>...>>;
    };
    template<typename ... Ts>
    using result = typename helper<Ts...>::type;
  };
};

}
#endif //TYPICAL_PARTITION_HPP
