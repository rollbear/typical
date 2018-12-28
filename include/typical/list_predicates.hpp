#ifndef TYPICAL_LIST_PREDICATES_HPP
#define TYPICAL_LIST_PREDICATES_HPP

#include <typical/function_support.hpp>
#include <typical/type_predicates.hpp>
#include <typical/application.hpp>

#include <utility>

namespace typical {

struct is_empty {
  template<typename>
  struct helper {
    static constexpr bool value = false;
  };
  template<template<typename...> class L>
  struct helper<L<>> {
    static constexpr bool value = true;
  };
  using continuation = identity;
  template<typename C = continuation>
  struct to {
    using TO = detail::to<C>;
    template<typename ... Vs>
    using result = typename TO::template result<constant<helper<Vs...>::value>>;
  };
};

template<typename P>
struct any_of {
  using continuation = identity;
  template<typename C = continuation>
  struct to {
    using TO = detail::to<C>;
    template<typename ...Ts>
    using result = typename TO::template result<constant<std::disjunction_v<apply_pack<P, Ts>...>>>;
  };
};

template<typename P>
struct all_of {
  using continuation = identity;
  template<typename C = continuation>
  struct to {
    using TO = detail::to<C>;
    template<typename ... Ts>
    using result = typename TO::template result<constant<std::conjunction_v<apply_pack<P, Ts>...>>>;
  };
};

template<typename P>
using none_of = negate<any_of<P>>;

template<typename T>
using has = any_of<is_same<T>>;

namespace detail {
template<typename ...>
struct unique;

template<typename T>
struct unique<T> {
  static constexpr auto value = true;
};

template<typename T, typename ...Ts>
struct unique<T, Ts...> {
  static constexpr auto value =
    !apply_pack<has<T>, Ts...>::value && unique<Ts...>::value;
};
}

struct all_unique {
  using continuation = identity;
  template<typename C = continuation>
  struct to {
    template<typename ... Ts>
    using result = apply_one<C, constant<detail::unique<Ts...>::value>>;
  };
};
}
#endif //TYPICAL_LIST_PREDICATES_HPP
