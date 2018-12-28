#ifndef TYPICAL_TYPICAL_HPP
#define TYPICAL_TYPICAL_HPP

#include <typical/constant.hpp>
#include <typical/conditional.hpp>
#include <typical/function_support.hpp>
#include <typical/compose.hpp>
#include <typical/type_manipulation.hpp>
#include <typical/type_predicates.hpp>
#include <typical/list_predicates.hpp>
#include <typical/application.hpp>
#include <typical/algorithms/transform.hpp>
#include <typical/algorithms/join.hpp>
#include <typical/algorithms/size.hpp>
#include <typical/algorithms/filter.hpp>
#include <typical/algorithms/partition.hpp>
#include <typical/algorithms/drop_front.hpp>
#include <typical/algorithms/take.hpp>
#include <typical/algorithms/count_if.hpp>
#include <typical/algorithms/index_of.hpp>
#include <typical/algorithms/front.hpp>
#include <typical/utilities.hpp>
#include <type_traits>
#include <utility>

namespace typical {

template<typename T>
using identity_t = apply_one<identity, T>;

template<typename T>
struct identity_template;

template<template<typename ...> class L, typename ... Ts>
struct identity_template<L<Ts...>> : make<L> {
};

template<typename F>
struct zip {
  using continuation = make<list>;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;
    template<typename L1, typename L2>
    struct helper;
    template<template<typename ...> class L1, typename ... L1s,
      template<typename...> class L2, typename ... L2s>
    struct helper<L1<L1s...>, L2<L2s...>> {
      using type = typename TO::template result< apply_pack<F,L1s, L2s>...>;
    };
    template<typename L1, typename L2>
    using result = typename helper<L1, L2>::type;
  };
};


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

struct reverse {
  using continuation = make<list>;
  template<typename C = continuation>
  struct to {
    using TO = detail::to<C>;
    template<std::size_t N, typename, bool>
    struct helper;

    template<template<typename ...> class L, typename ... Ts>
    struct helper<0, L<Ts...>, false> {
      using type = L<Ts...>;
    };
    template<template<typename...> class L, typename T, typename ... Ts>
    struct helper<1, L<T, Ts...>, false> {
      using type = L<T, Ts...>;
    };
    template<template<typename ...> class L, typename T1, typename T2, typename ... Ts>
    struct helper<2, L<T1, T2, Ts...>, false> {
      using type = L<T2, T1, Ts...>;
    };
    template<template<typename ...> class L, typename T1, typename T2, typename T3, typename ... Ts>
    struct helper<3, L<T1, T2, T3, Ts...>, false> {
      using type = L<T3, T2, T1, Ts...>;
    };
    template<template<typename ...> class L, typename T1, typename T2, typename T3, typename T4, typename ... Ts>
    struct helper<4, L<T1, T2, T3, T4, Ts...>, false> {
      using type = L<T4, T3, T2, T1, Ts...>;
    };
    template<template<typename ...> class L, typename T1, typename T2, typename T3, typename T4, typename T5, typename ... Ts>
    struct helper<5, L<T1, T2, T3, T4, T5, Ts...>, false> {
      using type = L<T5, T4, T3, T2, T1, Ts...>;
    };
    template<template<typename ...> class L, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename ... Ts>
    struct helper<6, L<T1, T2, T3, T4, T5, T6, Ts...>, false> {
      using type = L<T6, T5, T4, T3, T2, T1, Ts...>;
    };
    template<template<typename ...> class L, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename ... Ts>
    struct helper<7, L<T1, T2, T3, T4, T5, T6, T7, Ts...>, false> {
      using type = L<T7, T6, T5, T4, T3, T2, T1, Ts...>;
    };
    template<template<typename ...> class L, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename ... Ts>
    struct helper<8, L<T1, T2, T3, T4, T5, T6, T7, T8, Ts...>, false> {
      using type = L<T8, T7, T6, T5, T4, T3, T2, T1, Ts...>;
    };
    template<template<typename ...> class L, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename ... Ts>
    struct helper<9, L<T1, T2, T3, T4, T5, T6, T7, T8, T9, Ts...>, false> {
      using type = L<T9, T8, T7, T6, T5, T4, T3, T2, T1, Ts...>;
    };
    template<std::size_t N, template<typename ...> class L, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename ... Ts>
    struct helper<N, L<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, Ts...>, true> {
      using type = apply_pack_to<join, TO, typename helper<
        N - 10, L<Ts...>, (N >= 20)>::type, L<T10, T9, T8, T7, T6, T5, T4, T3, T2, T1>>;
    };
    template<typename ...T>
    using result = typename helper<sizeof...(T), typename TO::template result<T...>, (sizeof...(T) >= 10)>::type;
  };
};

struct flatten
{
  using continuation = make<list>;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;
    template<typename T>
    struct helper;
    template<template<typename ...> class L, typename ... Ts>
    struct helper<L<Ts...>> {
      template<typename V>
      struct split {
        using type = L<V>;
      };
      template<typename ... Vs>
      struct split<L<Vs...>> {
        using type = apply_pack_to<join, TO, typename split<Vs>::type...>;
      };
      using type = apply_pack_to<join, TO, typename split<Ts>::type...>;
    };
    template<typename T>
    using result = typename helper<T>::type;
  };
};


}

#endif //TYPICAL_TYPICAL_HPP
