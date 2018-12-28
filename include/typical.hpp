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
#include <typical/algorithms/at.hpp>
#include <typical/algorithms/reverse.hpp>
#include <typical/algorithms/flatten.hpp>
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

}

#endif //TYPICAL_TYPICAL_HPP
