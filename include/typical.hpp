#ifndef TYPICAL_TYPICAL_HPP
#define TYPICAL_TYPICAL_HPP

#include <type_traits>

namespace typical {

template<typename...>
struct type_list {};

template<typename F, typename ... Ts>
using apply = typename F::template f<Ts...>;

struct identity {
  template <typename T>
  struct S {
    using type= T;
  };
  template<typename ...T>
  using f = typename S<T...>::type;
};

template<typename T>
using identity_t = apply<identity, T>;

template<template<typename ...> class C>
struct make {
  template<typename ... T>
  using f = C<T...>;
};


template<typename T>
struct identity_template;

template<template<typename ...> class L, typename ... T>
struct identity_template<L<T...>> : make<L> {
};

template <template <typename ...> class T, typename ... Ts>
struct bind_front {
  template <typename ... Vs>
  struct helper {
    using type = T<Ts..., Vs...>;
  };
  template <typename ... Vs>
  using f = typename helper<Vs...>::type;
};

template<template<typename ...> class T, typename C = identity>
struct from_type {
  template <typename ... Vs>
  struct helper {
    using type = typename T<Vs...>::type;
  };
  template<typename ... Vs>
  using f = apply<C, typename helper<Vs...>::type>;
};


template<auto V>
using constant = std::integral_constant<std::remove_cv_t<decltype(V)>, V>;

template<auto V>
inline constexpr auto constant_v = constant<V>::value;

template <template <typename ...> class T, typename C = identity>
struct from_value
{
  template <typename ... Vs>
  using f = apply<C, constant<T<Vs...>::value>>;
};

template <typename C = identity>
using add_pointer = from_type<std::add_pointer, C>;

template <typename C = identity>
using add_lvalue_reference = from_type<std::add_lvalue_reference, C>;

template <typename C = identity>
using add_rvalue_reference = from_type<std::add_rvalue_reference, C>;

template <typename C = identity>
using add_const = from_type<std::add_const, C>;

template <typename C = identity>
using add_volatile = from_type<std::add_volatile, C>;

template <typename C = identity>
using remove_reference = from_type<std::remove_reference, C>;

template <typename C = identity>
using remove_pointer = from_type<std::remove_pointer, C>;

template <typename C = identity>
using remove_const = from_type<std::remove_const, C>;

template <typename C = identity>
using remove_volatile = from_type<std::remove_volatile, C>;

template <typename T, typename C = identity>
using is_same = from_type<bind_front<std::is_same, T>::template f, C>;

template <typename C = identity>
using is_pointer = from_value<std::is_pointer, C>;

template <typename C = identity>
using is_reference = from_value<std::is_reference, C>;

template <typename C = identity>
using is_lvalue_reference = from_value<std::is_lvalue_reference, C>;

template <typename C = identity>
using is_rvalue_reference = from_value<std::is_rvalue_reference, C>;

template <typename C = identity>
using is_const = from_value<std::is_const, C>;

template <typename C = identity>
using is_volatile = from_value<std::is_volatile, C>;

template<template<typename ...> class T, typename U>
struct is_template_t : std::false_type {
};

template<template<typename ...> class T, typename ... Ts>
struct is_template_t<T, T<Ts...>> : std::true_type {
};

template<template<typename ...> class T, typename C = identity>
struct is_template {
  template<typename U>
  using f = apply<C, constant<is_template_t<T, U>::value>>;
};

template<typename F, typename C = identity>
struct negate {
  template<typename T>
  using f = apply<C, constant<!apply<F, T>::value>>;
};

template<template <typename ...> class... Fs>
struct compose;

template<>
struct compose<> {
  template <typename C = make<type_list>>
  struct type {
    template<typename ...T>
    using f = apply<C, T...>;
  };
};

template<template <typename...> class F, template <typename ...> class ... Fs>
struct compose<F, Fs...> {
  template <typename C = make<type_list>>
  struct type {
    template<typename ...T>
    using f = apply<typename compose<Fs...>::template type<F<C>>, T...>;
  };
};


template <typename C = identity>
using remove_cv = typename compose<remove_volatile, remove_const>::template type<C>;

//template <typename C = identity>
//using remove_cv_ref = typename compose<typename remove_cv::type, remove_reference>::template type<C>;

template<typename F, typename C = make<type_list>>
struct transform {
  template<typename ... Ts>
  using f = apply<C, apply<F, Ts>...>;
};

template <typename C = make<type_list>>
struct unwrap {
  template <typename T>
  struct helper
  {
    using type = apply<C, T>;
  };
  template <template <typename ...> class L, typename... Ts>
  struct helper<L<Ts...>>
  {
    using type = apply<C, Ts...>;
  };
  template <typename ...Ts>
  using f = typename helper<Ts...>::type;
};

template <template <typename ...> class C>
struct metamorph
{
  template <typename ... Ts>
  using f = apply<unwrap<make<C>>, Ts...>;
};

template<typename L, template<typename ...> class D>
using metamorph_t = apply<metamorph<D>, L>;


template <typename C = make<type_list>>
struct concat
{
  template <typename ...Ts>
  struct helper;
  template <template<typename...> class L, typename ...Ts, typename ...Vs, typename ...Tail>
  struct helper<L<Ts...>, L<Vs...>, Tail...>
  {
    using type = typename helper<L<Ts...,Vs...>, Tail...>::type;
  };
  template <template <typename...> class L, typename ... Ts>
  struct helper<L<Ts...>>
  {
    using type = apply<C, Ts...>;
  };
  template <typename ... Ts>
  using f = typename helper<Ts...>::type;
};

struct size {
  template<typename>
  struct helper;
  template<template<typename ...> class L, typename ... Ts>
  struct helper<L<Ts...>> {
    static constexpr std::size_t value = sizeof...(Ts);
  };
  template<typename T>
  using f = constant<helper<T>::value>;
};


template<typename F, typename C = make<type_list>>
struct zip {
  template<typename L1, typename L2>
  struct helper;
  template<template<typename ...> class L1, typename ... L1s,
    template<typename...> class L2, typename ... L2s>
  struct helper<L1<L1s...>, L2<L2s...>> {
    using type = apply<C, apply<F, L1s, L2s>...>;
  };
  template<typename L1, typename L2>
  using f = typename helper<L1, L2>::type;
};

template<typename L1, typename L2, typename F, typename C = make<type_list>>
using zip_t = apply<zip<F, C>, L1, L2>;


template<bool>
struct conditional {
  template<typename T, typename>
  using f = T;
};

template<>
struct conditional<false> {
  template<typename, typename U>
  using f = U;
};

template<bool b, typename T, typename U>
using conditional_t = apply<conditional<b>, T, U>;

template<typename P, typename C = make<type_list>>
struct filter {
  template<typename L>
  struct helper {
    using type = L;
  };
  template<template<typename...> class L, typename ... Ts>
  struct helper<L<Ts...>> {
    using type = apply<concat<C>, conditional_t<apply<P, Ts>::value, L<Ts>, L<>>...>;
  };
  template<typename ... Ts>
  using f = typename helper<Ts...>::type;
};



template<typename P, typename L>
using filter_t = apply<filter<P>, L>;

template<typename P, typename C = make<type_list>>
struct partition {
  template<typename ... Ts>
  using f = apply<C, apply<concat<make<type_list>>,conditional_t<apply<P, Ts>::value, type_list<Ts>, type_list<>>...>,
    apply<concat<make<type_list>>, conditional_t<apply<P, Ts>::value, type_list<>, type_list<Ts>>...>>;
};



template <typename C = identity>
struct front {
  template<typename T, typename ...>
  using f = apply<C, T>;
};


template<auto ... I>
inline constexpr auto sum = (I + ...);

template<typename P, typename C = identity>
struct count_if {
  template<typename ...T>
  using f = apply<C, constant<sum<0UL, apply<P, T>::value...>>>;
};

template<typename P, typename L, typename C = identity>
using count_if_t = apply<count_if<P>, L, C>;

template<typename P, typename L>
constexpr inline auto count_if_v = count_if_t<P, L>::value;


template<typename P, typename C = identity>
struct any_of {
  template<typename>
  struct helper;
  template<template<typename ...> class L, typename ... Ts>
  struct helper<L<Ts...>> {
    static constexpr auto value = std::disjunction_v<apply<P, Ts>...>;
  };
  template<typename T>
  using f = apply<C, constant<helper<T>::value>>;
};

template<typename P, typename C = identity>
struct all_of {
  template<typename>
  struct helper;
  template<template<typename ...> class L, typename ... Ts>
  struct helper<L<Ts...>> {
    static constexpr auto value = std::conjunction_v<apply<P, Ts>...>;
  };
  template<typename T>
  using f = apply<C, constant<helper<T>::value>>;
};

template<typename P, typename C = identity>
using none_of = negate<any_of<P>, C>;

static constexpr unsigned log2(unsigned n, unsigned count=0)
{
  return n ? log2(n/2, count+1) : count;
}

template<typename N, typename C = make<type_list>>
struct drop_first
{
  template <int I, int K, bool, typename ...>
  struct helper;
  template<int K, typename ... Ts>
  struct helper<0, K, false,Ts...>
  {
    using type = apply<C, Ts...>;
  };
  template <int K, typename T1, typename ... Ts>
  struct helper<1, K, false,T1, Ts...>
  {
    using type = apply<C, Ts...>;
  };
  template <int K, typename T1, typename T2, typename ... Ts>
  struct helper<2, K, false,T1, T2, Ts...>
  {
    using type = typename helper<log2(K-2), K - 2, false,Ts...>::type;
  };
  template <int K, typename T1, typename T2, typename T3, typename T4, typename ... Ts>
  struct helper<3, K, false,T1, T2, T3, T4, Ts...>
  {
    using type = typename helper<log2(K-4), K - 4, false,Ts...>::type;
  };
  template <int K, typename T1, typename T2, typename T3, typename T4,
    typename T5, typename T6, typename T7, typename T8, typename ... Ts>
    struct helper<4, K, false,T1,T2,T3,T4,T5,T6,T7,T8,Ts...>
    {
      using type = typename helper<log2(K-8), K - 8, false,Ts...>::type;
    };
  template <int K, typename T1, typename T2, typename T3, typename T4,
    typename T5, typename T6, typename T7, typename T8,
    typename T9, typename T10, typename T11, typename T12,
    typename T13, typename T14, typename T15, typename T16,
    typename ... Ts>
  struct helper<5, K, false,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,Ts...>
  {
    using type = typename helper<log2(K-16), K - 16, false,Ts...>::type;
  };
  template <int I, int K, typename T1, typename T2, typename T3, typename T4,
    typename T5, typename T6, typename T7, typename T8,
    typename T9, typename T10, typename T11, typename T12,
    typename T13, typename T14, typename T15, typename T16,
    typename ... Ts>
  struct helper<I, K, true,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,Ts...>
  {
    using type = typename helper<log2(K-16), K - 16, (K>=32), Ts...>::type;
  };
  template <typename ... Ts>
  using f = typename helper<log2(N::value), N::value, (N::value>=32), Ts...>::type;
};

template <typename N, typename C = identity>
struct nth_type
{
  template <typename ...Ts>
  using f = apply<drop_first<N, front<C>>, Ts...>;
};

template<typename C = make<type_list>>
struct reverse
{
  template <std::size_t N, typename, bool = (N >= 10)>
  struct helper;

  template <template <typename ...> class L, typename ... Ts>
    struct helper<0,L<Ts...>, false>
    {
      using type = L<Ts...>;
    };
  template <template <typename...> class L, typename T, typename ... Ts>
    struct helper<1,L<T,Ts...>, false>
    {
      using type = L<T, Ts...>;
    };
  template <template <typename ...> class L, typename T1, typename T2, typename ... Ts>
    struct helper<2, L<T1, T2, Ts...>, false>
    {
      using type = L<T2, T1, Ts...>;
    };
  template <template <typename ...> class L, typename T1, typename T2, typename T3, typename ... Ts>
  struct helper<3,L<T1, T2, T3, Ts...>, false>
  {
    using type = L<T3, T2, T1, Ts...>;
  };
  template <template <typename ...> class L, typename T1, typename T2, typename T3, typename T4, typename ... Ts>
  struct helper<4, L<T1, T2, T3, T4, Ts...>, false>
  {
    using type = L<T4, T3, T2, T1, Ts...>;
  };
  template <template <typename ...> class L, typename T1, typename T2, typename T3, typename T4, typename T5, typename ... Ts>
  struct helper<5, L<T1, T2, T3, T4, T5, Ts...>, false>
  {
    using type = L<T5, T4, T3, T2, T1, Ts...>;
  };
  template <template <typename ...> class L, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename ... Ts>
  struct helper<6, L<T1, T2, T3, T4, T5, T6, Ts...>, false>
  {
    using type = L<T6, T5, T4, T3, T2, T1, Ts...>;
  };
  template <template <typename ...> class L, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename ... Ts>
  struct helper<7, L<T1, T2, T3, T4, T5, T6, T7, Ts...>, false>
  {
    using type = L<T7, T6, T5, T4, T3, T2, T1, Ts...>;
  };
  template <template <typename ...> class L, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename ... Ts>
  struct helper<8, L<T1, T2, T3, T4, T5, T6, T7, T8, Ts...>, false>
  {
    using type = L<T8, T7, T6, T5, T4, T3, T2, T1, Ts...>;
  };
  template <template <typename ...> class L, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename ... Ts>
  struct helper<9, L<T1, T2, T3, T4, T5, T6, T7, T8, T9, Ts...>, false>
  {
    using type = L<T9, T8, T7, T6, T5, T4, T3, T2, T1, Ts...>;
  };
  template <std::size_t N, template <typename ...> class L, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename ... Ts>
  struct helper<N, L<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, Ts...>, true>
  {
    using type = apply<concat<C>, typename helper<N-10, L<Ts...>>::type, L<T10, T9, T8, T7, T6, T5, T4, T3, T2, T1>>;
  };
  template <typename ...T>
  using f = typename helper<sizeof...(T), apply<C,T...>>::type;
};

template <typename C = make<type_list>>
struct flatten
{
  template <typename T>
  struct helper;
  template <template <typename ...> class L, typename ... Ts>
  struct helper<L<Ts...>>
  {
    template <typename V>
    struct split {
      using type = L<V>;
    };
    template <typename ... Vs>
    struct split<L<Vs...>>{
      using type = apply<concat<C>,typename split<Vs>::type...>;
    };
    using type = apply<concat<C>, typename split<Ts>::type...>;
  };
  template <typename T>
  using f = typename helper<T>::type;
};

}

#endif //TYPICAL_TYPICAL_HPP
