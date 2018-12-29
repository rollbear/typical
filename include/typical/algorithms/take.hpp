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


#ifndef TYPICAL_TAKE_HPP
#define TYPICAL_TAKE_HPP

#include <typical/function_support.hpp>
#include <typical/application.hpp>
#include <typical/algorithms/join.hpp>

namespace typical
{
template <typename N>
struct take
{
  using continuation = make<list>;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;

    template<std::size_t I, std::size_t L, bool, typename ...>
    struct helper;

    template<typename ... Ts>
    struct helper<0, 0, false, Ts...> {
      using type = list<>;
    };

    template<typename T, typename ... Ts>
    struct helper<1, 0, false, T, Ts...> {
      using type = list<T>;
    };
    template<std::size_t I, typename T0, typename T1, typename ... Ts>
    struct helper<I, 1, false, T0, T1, Ts...> {
      using type = apply_pack<join, list<T0, T1>, typename helper<
        I - 2, detail::log2(I - 2), false, Ts...>::type>;
    };
    template<std::size_t I, typename T0, typename T1, typename T2, typename T3, typename ... Ts>
    struct helper<I, 2, false, T0, T1, T2, T3, Ts...> {
      using type = apply_pack<join, list<T0, T1, T2, T3>, typename helper<
        I - 4, detail::log2(I - 4), false, Ts...>::type>;
    };
    template<std::size_t I,
      typename T0, typename T1, typename T2, typename T3,
      typename T4, typename T5, typename T6, typename T7,
      typename ... Ts>
    struct helper<I, 3, false, T0, T1, T2, T3, T4, T5, T6, T7, Ts...> {
      using type = apply_pack<join, list<T0, T1, T2, T3, T4, T5, T6, T7>, typename helper<
        I - 8, detail::log2(I - 8), false, Ts...>::type>;
    };
    template<std::size_t I, std::size_t L,
      typename T0, typename T1, typename T2, typename T3,
      typename T4, typename T5, typename T6, typename T7,
      typename T8, typename T9, typename T10, typename T11,
      typename T12, typename T13, typename T14, typename T15,
      typename ... Ts>
    struct helper<I, L, true, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, Ts...> {
      using type = apply_pack<join, list<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15>, typename helper<
        I - 16, detail::log2(I - 16), (I >= 32), Ts...>::type>;
    };
    template<typename ... Ts>
    using result = apply_pack_to<unwrap, TO, typename helper<N::value, detail::log2(
      N::value), (int(N::value) > 15), Ts...>::type>;
  };
};

}
#endif //TYPICAL_TAKE_HPP
