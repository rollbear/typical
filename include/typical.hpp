#ifndef TYPICAL_TYPICAL_HPP
#define TYPICAL_TYPICAL_HPP

#include <typical/constant.hpp>
#include <typical/conditional.hpp>

#include <type_traits>
#include <utility>

namespace typical {


template <typename F, typename C, typename ... Ts>
using apply_to = typename F::template to<C>::template result<Ts...>;
template <typename F, typename ... Ts>
using apply_pack = typename F::template to<typename F::continuation>::template result<Ts...>;

//template<typename F, typename ... Ts>
//using apply_pack = typename F::template result<Ts...>;

template <typename F, typename T>
using apply_one = typename F::template result<T>;

namespace detail {
static constexpr unsigned log2(unsigned n, unsigned b = 16)
{
  if (n <= 1) return 0;
  const auto hm = ~((1U << b) - 1U);
  return n & hm ? b + detail::log2(n >> b, b >> 1) : detail::log2(n, b >> 1);
}

template <typename T>
struct proxy;

template <typename T, typename = void>
struct has_continuation : std::false_type{};

template <typename T>
struct has_continuation<T, std::void_t<typename T::continuation>>
  : std::true_type {};

template <typename T, bool = has_continuation<T>::value>
struct to_
{
  using type = T;
};

template <typename T>
struct to_<T, true>
{
  using type = typename T::template to<typename T::continuation>;
};


template <typename T>
using to = typename to_<T>::type;

}

template<typename...>
struct list {};

struct identity {
  template<typename T>
  using result = T;
};

template<typename T>
using identity_t = apply_one<identity, T>;

template<template<typename ...> class C>
struct make {
  template<typename ... Ts>
  using result = C<Ts...>;
};

namespace detail {

template<template<typename ...> class, typename, typename>
struct make_n;

template<template<typename ...> class C, typename T, std::size_t ... Is>
struct make_n<C, T, std::index_sequence<Is...>> {
  template<std::size_t>
  using made = T;
  using type = C<made<Is>...>;
};

}
template <template <typename ...> class C, typename N, typename T>
using make_n = typename detail::make_n<C, T, std::make_index_sequence<N::value>>::type;


template<typename T>
struct identity_template;

template<template<typename ...> class L, typename ... Ts>
struct identity_template<L<Ts...>> : make<L> {
};

template <typename ...>
struct compose;

template <>
struct compose<>
{
  using continuation = identity;
  template <typename C = continuation>
  struct to
  {
    using T = detail::to<C>;
    template <typename ... Ts>
    using result = typename T::template result<Ts...>;
  };
};

template <typename F, typename ... Fs>
struct compose<F, Fs...>
{
  using continuation = typename F::continuation;
  template <typename C = continuation>
  struct to
  {
    template <typename ... Ts>
    using result = apply_to<compose<Fs...>, typename F::template to<C>, Ts...>;
  };
};

template <template <typename ...> class T, typename ... Ts>
struct bind_front {
  template <typename ... Vs>
  struct helper {
    using type = T<Ts..., Vs...>;
  };
  template <typename ... Vs>
  using result = typename helper<Vs...>::type;
};

template<template <typename...> class T>
struct from_type {
  using continuation = identity;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;
    template<typename ... Vs>
    struct helper {
      using type = typename TO::template result<typename T<Vs...>::type>;
    };
    template<typename ... Vs>
    using result = typename helper<Vs...>::type;
  };
};


struct is_empty
{
  template <typename>
  struct helper { static constexpr bool value = false;};
  template <template <typename...> class L>
  struct helper<L<>> { static constexpr bool value = true;};
  using continuation = identity;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;
    template<typename ... Vs>
    using result = typename TO::template result<constant<helper<Vs...>::value>>;
  };
};


template <template <typename ...> class T>
struct from_value
{
  using continuation = identity;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;
    template<typename ... Vs>
    using result = typename TO::template result<constant<T<Vs...>::value>>;
  };
};

using add_pointer = from_type<std::add_pointer>;
using add_lvalue_reference = from_type<std::add_lvalue_reference>;
using add_rvalue_reference = from_type<std::add_rvalue_reference>;
using add_const = from_type<std::add_const>;
using add_volatile = from_type<std::add_volatile>;
using remove_reference = from_type<std::remove_reference>;
using remove_pointer = from_type<std::remove_pointer>;
using remove_const = from_type<std::remove_const>;
using remove_volatile = from_type<std::remove_volatile>;
using is_pointer = from_value<std::is_pointer>;
using is_reference = from_value<std::is_reference>;
using is_lvalue_reference = from_value<std::is_lvalue_reference>;
using is_rvalue_reference = from_value<std::is_rvalue_reference>;
using is_const = from_value<std::is_const>;
using is_volatile = from_value<std::is_volatile>;

template <typename T>
using is_same = from_type<bind_front<std::is_same, T>::template result>;


template<template<typename ...> class T, typename U>
struct is_template_t {
  using type = constant<false>;
};

template<template<typename ...> class T, typename ... Ts>
struct is_template_t<T, T<Ts...>> {
  using type = constant<true>;
};

template<template<typename ...> class T>
struct is_template {
  using continuation = identity;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;
    template<typename U>
    using result = typename TO::template result<typename is_template_t<T, U>::type>;
  };
};

template<typename F>
struct negate {
  using continuation = identity;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;
    template<typename ...Ts>
    using result = typename TO::template result<constant<!apply_pack<F, Ts...>::value>>;
  };
};


using remove_cv = compose<remove_volatile,remove_const>;
using remove_cv_ref = compose<remove_cv, remove_reference>;

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

struct unwrap {
  using continuation = make<list>;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;
    template<typename T>
    struct helper {
      using type = typename TO::template result<T>;
    };
    template<template<typename ...> class L, typename... Ts>
    struct helper<L<Ts...>> {
      using type = typename TO::template result<Ts...>;
    };
    template<typename ...Ts>
    using result = typename helper<Ts...>::type;
  };
};

template <template <typename ...> class C>
struct metamorph
{
  template <typename ... Ts>
  using result = apply_to<unwrap, make<C>, Ts...>;
};

template<typename L, template<typename ...> class D>
using metamorph_t = apply_one<metamorph<D>, L>;


struct join {
  using continuation = make<list>;
  template<typename C = continuation>
  struct to {
    using TO = detail::to<C>;
    template<int N, typename ...Ts>
    struct helper {
      using type = typename TO::template result<>;
    };

    template<template<typename...> class L, typename ... Ts>
    struct helper<0, L<Ts...>> {
      using type = typename TO::template result<Ts...>;
    };
    template<template<typename...> class L, typename ...T1s, typename ... T2s>
    struct helper<0, L<T1s...>, L<T2s...>> {
      using type = typename TO::template result<T1s..., T2s...>;
    };
    template<template<typename...> class L, typename ...T1s, typename ...T2s, typename ... Tail>
    struct helper<1, L<T1s...>, L<T2s...>, Tail...> {
      using type = typename helper<detail::log2(
        sizeof...(Tail) + 1), L<T1s..., T2s...>, Tail...>::type;
    };
    template<template<typename...> class L, typename ...T1s, typename ...T2s, typename ...T3s, typename ...T4s, typename ... Tail>
    struct helper<2, L<T1s...>, L<T2s...>, L<T3s...>, L<T4s...>, Tail...> {
      using type = typename helper<detail::log2(
        sizeof...(Tail) + 1), L<T1s..., T2s..., T3s..., T4s...>, Tail...>::type;
    };
    template<template<typename...> class L, typename ...T1s, typename ...T2s, typename ...T3s, typename ...T4s,
      typename ...T5s, typename ...T6s, typename...T7s, typename ...T8s, typename ... Tail>
    struct helper<3, L<T1s...>, L<T2s...>, L<T3s...>, L<T4s...>, L<T5s...>, L<T6s...>, L<T7s...>, L<T8s...>,
      Tail...> {
      using type = typename helper<detail::log2(sizeof...(Tail) +
                                                1), L<T1s..., T2s..., T3s..., T4s..., T5s..., T6s..., T7s..., T8s...>, Tail...>::type;
    };
    template<template<typename...> class L,
      typename ...T1s, typename ...T2s, typename ...T3s, typename ...T4s,
      typename ...T5s, typename ...T6s, typename... T7s, typename ...T8s,
      typename ...T9s, typename ...T10s, typename...T11s, typename ...T12s,
      typename ...T13s, typename ...T14s, typename...T15s, typename ...T16s, typename ... Tail>
    struct helper<4, L<T1s...>, L<T2s...>, L<T3s...>, L<T4s...>, L<T5s...>, L<T6s...>, L<T7s...>, L<T8s...>,
      L<T9s...>, L<T10s...>, L<T11s...>, L<T12s...>, L<T13s...>, L<T14s...>, L<T15s...>, L<T16s...>,
      Tail...> {
      using type = typename helper<detail::log2(sizeof...(Tail) +
                                                1), L<T1s..., T2s..., T3s..., T4s..., T5s..., T6s..., T7s..., T8s..., T9s..., T10s..., T11s..., T12s..., T13s..., T14s..., T15s..., T16s...>, Tail...>::type;
    };
    template<template<typename...> class L,
      typename ...T1s, typename ...T2s, typename ...T3s, typename ...T4s,
      typename ...T5s, typename ...T6s, typename... T7s, typename ...T8s,
      typename ...T9s, typename ...T10s, typename...T11s, typename ...T12s,
      typename ...T13s, typename ...T14s, typename...T15s, typename ...T16s,
      typename ...T17s, typename ...T18s, typename...T19s, typename ...T20s,
      typename ...T21s, typename ...T22s, typename...T23s, typename ...T24s,
      typename ...T25s, typename ...T26s, typename...T27s, typename ...T28s,
      typename ...T29s, typename ...T30s, typename...T31s, typename ...T32s,
      typename ... Tail>
    struct helper<5, L<T1s...>, L<T2s...>, L<T3s...>, L<T4s...>, L<T5s...>, L<T6s...>, L<T7s...>, L<T8s...>,
      L<T9s...>, L<T10s...>, L<T11s...>, L<T12s...>, L<T13s...>, L<T14s...>, L<T15s...>, L<T16s...>,
      L<T17s...>, L<T18s...>, L<T19s...>, L<T20s...>, L<T21s...>, L<T22s...>, L<T23s...>, L<T24s...>,
      L<T25s...>, L<T26s...>, L<T27s...>, L<T28s...>, L<T29s...>, L<T30s...>, L<T31s...>, L<T32s...>,
      Tail...> {
      using type = typename helper<detail::log2(sizeof...(Tail) +
                                                1), L<T1s..., T2s..., T3s..., T4s..., T5s..., T6s..., T7s..., T8s..., T9s..., T10s..., T11s..., T12s..., T13s..., T14s..., T15s..., T16s..., T17s..., T18s..., T19s..., T20s..., T21s..., T22s..., T23s..., T24s..., T25s..., T26s..., T27s..., T28s..., T29s..., T30s..., T31s..., T32s...>, Tail...>::type;
    };
    template<template<typename...> class L,
      typename ...T1s, typename ...T2s, typename ...T3s, typename ...T4s,
      typename ...T5s, typename ...T6s, typename... T7s, typename ...T8s,
      typename ...T9s, typename ...T10s, typename...T11s, typename ...T12s,
      typename ...T13s, typename ...T14s, typename...T15s, typename ...T16s,
      typename ...T17s, typename ...T18s, typename...T19s, typename ...T20s,
      typename ...T21s, typename ...T22s, typename...T23s, typename ...T24s,
      typename ...T25s, typename ...T26s, typename...T27s, typename ...T28s,
      typename ...T29s, typename ...T30s, typename...T31s, typename ...T32s,
      typename ...T33s, typename ...T34s, typename...T35s, typename ...T36s,
      typename ...T37s, typename ...T38s, typename...T39s, typename ...T40s,
      typename ...T41s, typename ...T42s, typename...T43s, typename ...T44s,
      typename ...T45s, typename ...T46s, typename...T47s, typename ...T48s,
      typename ...T49s, typename ...T50s, typename...T51s, typename ...T52s,
      typename ...T53s, typename ...T54s, typename...T55s, typename ...T56s,
      typename ...T57s, typename ...T58s, typename ...T59s, typename ...T60s,
      typename ...T61s, typename ...T62s, typename ...T63s, typename ...T64s,
      typename ... Tail>
    struct helper<6, L<T1s...>, L<T2s...>, L<T3s...>, L<T4s...>, L<T5s...>, L<T6s...>, L<T7s...>, L<T8s...>,
      L<T9s...>, L<T10s...>, L<T11s...>, L<T12s...>, L<T13s...>, L<T14s...>, L<T15s...>, L<T16s...>,
      L<T17s...>, L<T18s...>, L<T19s...>, L<T20s...>, L<T21s...>, L<T22s...>, L<T23s...>, L<T24s...>,
      L<T25s...>, L<T26s...>, L<T27s...>, L<T28s...>, L<T29s...>, L<T30s...>, L<T31s...>, L<T32s...>,
      L<T33s...>, L<T34s...>, L<T35s...>, L<T36s...>, L<T37s...>, L<T38s...>, L<T39s...>, L<T40s...>,
      L<T41s...>, L<T42s...>, L<T43s...>, L<T44s...>, L<T45s...>, L<T46s...>, L<T47s...>, L<T48s...>,
      L<T49s...>, L<T50s...>, L<T51s...>, L<T52s...>, L<T53s...>, L<T54s...>, L<T55s...>, L<T56s...>,
      L<T57s...>, L<T58s...>, L<T59s...>, L<T60s...>, L<T61s...>, L<T62s...>, L<T63s...>, L<T64s...>,
      Tail...> {
      using type = typename helper<detail::log2(sizeof...(Tail) +
                                                1), L<T1s..., T2s..., T3s..., T4s..., T5s..., T6s..., T7s..., T8s..., T9s..., T10s..., T11s..., T12s..., T13s..., T14s..., T15s..., T16s..., T17s..., T18s..., T19s..., T20s..., T21s..., T22s..., T23s..., T24s..., T25s..., T26s..., T27s..., T28s..., T29s..., T30s..., T31s..., T32s..., T33s..., T34s..., T35s..., T36s..., T37s..., T38s..., T39s..., T40s..., T41s..., T42s..., T43s..., T44s..., T45s..., T46s..., T47s..., T48s..., T49s..., T50s..., T51s..., T52s..., T53s..., T54s..., T50s..., T51s..., T52s..., T53s..., T54s..., T55s..., T56s..., T57s..., T58s..., T59s..., T60s..., T61s..., T62s..., T63s..., T64s...>, Tail...>::type;
    };
    template<int N, template<typename...> class L,
      typename ...T1s, typename ...T2s, typename ... T3s, typename ...T4s,
      typename ...T5s, typename ...T6s, typename ... T7s, typename ...T8s,
      typename ...T9s, typename ...T10s, typename ...T11s, typename ...T12s,
      typename ...T13s, typename ...T14s, typename ...T15s, typename ...T16s,
      typename ...T17s, typename ...T18s, typename ...T19s, typename ...T20s,
      typename ...T21s, typename ...T22s, typename ...T23s, typename ...T24s,
      typename ...T25s, typename ...T26s, typename ...T27s, typename ...T28s,
      typename ...T29s, typename ...T30s, typename ...T31s, typename ...T32s,
      typename ...T33s, typename ...T34s, typename ...T35s, typename ...T36s,
      typename ...T37s, typename ...T38s, typename ...T39s, typename ...T40s,
      typename ...T41s, typename ...T42s, typename ...T43s, typename ...T44s,
      typename ...T45s, typename ...T46s, typename ...T47s, typename ...T48s,
      typename ...T49s, typename ...T50s, typename ...T51s, typename ...T52s,
      typename ...T53s, typename ...T54s, typename ...T55s, typename ...T56s,
      typename ...T57s, typename ...T58s, typename ...T59s, typename ...T60s,
      typename ...T61s, typename ...T62s, typename ...T63s, typename ...T64s,
      typename ...T65s, typename ...T66s, typename ...T67s, typename ...T68s,
      typename ...T69s, typename ...T70s, typename ...T71s, typename ...T72s,
      typename ...T73s, typename ...T74s, typename ...T75s, typename ...T76s,
      typename ...T77s, typename ...T78s, typename ...T79s, typename ...T80s,
      typename ...T81s, typename ...T82s, typename ...T83s, typename ...T84s,
      typename ...T85s, typename ...T86s, typename ...T87s, typename ...T88s,
      typename ...T89s, typename ...T90s, typename ...T91s, typename ...T92s,
      typename ...T93s, typename ...T94s, typename ...T95s, typename ...T96s,
      typename ...T97s, typename ...T98s, typename ...T99s, typename ...T100s,
      typename ...T101s, typename ...T102s, typename ...T103s, typename ...T104s,
      typename ...T105s, typename ...T106s, typename ...T107s, typename ...T108s,
      typename ...T109s, typename ...T110s, typename ...T111s, typename ...T112s,
      typename ...T113s, typename ...T114s, typename ...T115s, typename ...T116s,
      typename ...T117s, typename ...T118s, typename ...T119s, typename ...T120s,
      typename ...T121s, typename ...T122s, typename ...T123s, typename ...T124s,
      typename ...T125s, typename ...T126s, typename ...T127s, typename ...T128s,
      typename ... Tail>
    struct helper<N, L<T1s...>, L<T2s...>, L<T3s...>, L<T4s...>, L<T5s...>, L<T6s...>, L<T7s...>, L<T8s...>,
      L<T9s...>, L<T10s...>, L<T11s...>, L<T12s...>, L<T13s...>, L<T14s...>, L<T15s...>, L<T16s...>,
      L<T17s...>, L<T18s...>, L<T19s...>, L<T20s...>, L<T21s...>, L<T22s...>, L<T23s...>, L<T24s...>,
      L<T25s...>, L<T26s...>, L<T27s...>, L<T28s...>, L<T29s...>, L<T30s...>, L<T31s...>, L<T32s...>,
      L<T33s...>, L<T34s...>, L<T35s...>, L<T36s...>, L<T37s...>, L<T38s...>, L<T39s...>, L<T40s...>,
      L<T41s...>, L<T42s...>, L<T43s...>, L<T44s...>, L<T45s...>, L<T46s...>, L<T47s...>, L<T48s...>,
      L<T49s...>, L<T50s...>, L<T51s...>, L<T52s...>, L<T53s...>, L<T54s...>, L<T55s...>, L<T56s...>,
      L<T57s...>, L<T58s...>, L<T59s...>, L<T60s...>, L<T61s...>, L<T62s...>, L<T63s...>, L<T64s...>,
      L<T64s...>, L<T65s...>, L<T66s...>, L<T67s...>, L<T68s...>, L<T69s...>, L<T70s...>, L<T71s...>,
      L<T72s...>, L<T73s...>, L<T74s...>, L<T75s...>, L<T76s...>, L<T77s...>, L<T78s...>, L<T79s...>,
      L<T80s...>, L<T81s...>, L<T82s...>, L<T83s...>, L<T84s...>, L<T85s...>, L<T86s...>, L<T87s...>,
      L<T88s...>, L<T89s...>, L<T90s...>, L<T91s...>, L<T92s...>, L<T93s...>, L<T94s...>, L<T95s...>,
      L<T96s...>, L<T97s...>, L<T98s...>, L<T99s...>, L<T100s...>, L<T101s...>, L<T102s...>, L<T103s...>,
      L<T104s...>, L<T105s...>, L<T106s...>, L<T107s...>, L<T108s...>, L<T109s...>, L<T110s...>, L<T111s...>,
      L<T112s...>, L<T113s...>, L<T114s...>, L<T115s...>, L<T116s...>, L<T117s...>, L<T118s...>, L<T119s...>,
      L<T120s...>, L<T121s...>, L<T122s...>, L<T123s...>, L<T124s...>, L<T125s...>, L<T126s...>, L<T127s...>,
      L<T128s...>, Tail...> {
      using type = typename helper<detail::log2(sizeof...(Tail) +
                                                1), L<T1s..., T2s..., T3s..., T4s..., T5s..., T6s..., T7s..., T8s..., T9s..., T10s..., T11s..., T12s..., T13s..., T14s..., T15s..., T16s..., T17s..., T18s..., T19s..., T20s..., T21s..., T22s..., T23s..., T24s..., T25s..., T26s..., T27s..., T28s..., T29s..., T30s..., T31s..., T32s..., T33s..., T34s..., T35s..., T36s..., T37s..., T38s..., T39s..., T40s..., T41s..., T42s..., T43s..., T44s..., T45s..., T46s..., T47s..., T48s..., T49s..., T50s..., T51s..., T52s..., T53s..., T54s..., T50s..., T51s..., T52s..., T53s..., T54s..., T55s..., T56s..., T57s..., T58s..., T59s..., T60s..., T61s..., T62s..., T63s..., T64s..., T65s..., T66s..., T67s..., T68s..., T69s..., T70s..., T71s..., T72s..., T73s..., T74s..., T75s..., T76s..., T77s..., T78s..., T79s..., T80s..., T81s..., T82s..., T83s..., T84s..., T85s..., T86s..., T87s..., T88s..., T89s..., T90s..., T91s..., T92s..., T93s..., T94s..., T95s..., T96s..., T97s..., T98s..., T99s..., T100s..., T101s..., T102s..., T103s..., T104s..., T105s..., T106s..., T107s..., T108s..., T109s..., T110s..., T111s..., T112s..., T113s..., T114s..., T115s..., T116s..., T117s..., T118s..., T119s..., T120s..., T121s..., T122s..., T123s..., T124s..., T125s..., T126s..., T127s..., T128s...>, Tail...>::type;
    };
    template<typename ... Ts>
    using result = typename helper<detail::log2(sizeof...(Ts)), Ts...>::type;
  };
};

struct size {
  template<typename>
  struct helper;
  template<template<typename ...> class L, typename ... Ts>
  struct helper<L<Ts...>> {
    static constexpr std::size_t value = sizeof...(Ts);
  };
  using continuation = identity;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;
    template<typename T>
    using result = apply_one<C, constant<helper<T>::value>>;
  };
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


template<typename P>
struct filter
{
  using continuation = make<list>;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;
    template<typename ... Ts>
    using result = typename join::template to<TO>::template result<conditional_t<apply_pack<P, Ts>::value, list<Ts>, list<>>...>;
  };
};



template <typename N>
struct drop_front
{
  using continuation = make<list>;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;

    template<typename>
    struct helper;

    template<typename ... Vs>
    struct helper<list<Vs...>> {
      template<typename ... Ts>
      static typename TO::template result<Ts...> func(Vs..., detail::proxy<Ts> *...);
    };

    template<typename ... Ts>
    using result = decltype(helper<make_n<list, N, const void *>>::func(
      static_cast<detail::proxy<Ts> *>(nullptr)...));
  };
};

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
    using result = apply_to<unwrap, TO, typename helper<N::value, detail::log2(
      N::value), (int(N::value) > 15), Ts...>::type>;
  };
};

template<typename P>
struct partition {
  using continuation = make<list>;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;
    template<typename ... Ts>
    struct helper {
      using type = typename TO::template result<apply_to<join, make<list>, conditional_t<apply_pack<P, Ts>::value, list<Ts>, list<>>...>,
        apply_to<join, make<list>, conditional_t<apply_pack<P, Ts>::value, list<>, list<Ts>>...>>;
    };
    template<typename ... Ts>
    using result = typename helper<Ts...>::type;
  };
};



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


template<typename P>
struct count_if {
  using continuation = identity;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;

    template<auto ... Is>
    static constexpr auto sum = (...  + Is);

    template<typename T>
    using eval = apply_pack<P, T>;
    template<typename ...Ts>
    using result = typename TO::template result<constant<sum<eval<Ts>::value...>>>;
  };
};

template<typename P>
struct any_of {
  using continuation = identity;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;
    template<typename ...Ts>
    using result = typename TO::template result<constant<std::disjunction_v<apply_pack<P, Ts>...>>>;
  };
};

template<typename P>
struct all_of {
  using continuation = identity;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;
    template<typename ... Ts>
    using result = typename TO::template result<constant<std::conjunction_v<apply_pack<P, Ts>...>>>;
  };
};

template<typename P>
using none_of = negate<any_of<P>>;

template <typename N>
struct at
{
  using continuation = identity;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;
    template<typename ...Ts>
    using result = apply_to<compose<front, drop_front<N>>, TO, Ts...>;
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
      using type = apply_to<join, TO, typename helper<
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
        using type = apply_to<join, TO, typename split<Vs>::type...>;
      };
      using type = apply_to<join, TO, typename split<Ts>::type...>;
    };
    template<typename T>
    using result = typename helper<T>::type;
  };
};

template <typename T>
using has = any_of<is_same<T>>;

template <typename T>
struct index_of
{
  template <std::size_t ... Is, typename ... Ts>
  static constexpr auto index_func(std::index_sequence<Is...>, detail::proxy<Ts>*...)
  {
    constexpr auto i = (((std::is_same_v<T,Ts>*(Is+1)) + ...));
    return int(i)-1;
  }
  template <typename ... Ts>
  static constexpr auto index_func(detail::proxy<Ts>*... p)
  {
    return index_func(std::index_sequence_for<Ts...>{}, p...);
  }

  using continuation = identity;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;

    template <typename ... Ts>
    using result = apply_one<TO,constant<index_func(static_cast<detail::proxy<Ts>*>(nullptr)...)>>;
  };
};

namespace detail {
  template <typename ...>
  struct unique;

  template <typename T>
  struct unique<T>
  {
    static constexpr auto value = true;
  };

  template <typename T, typename ...Ts>
  struct unique<T, Ts...>
  {
    static constexpr auto value = !apply_pack<has<T>, Ts...>::value && unique<Ts...>::value;
  };
}

struct all_unique
{
  using continuation = identity;
  template <typename C = continuation>
  struct to {
    template <typename ... Ts>
    using result = apply_one<C, constant<detail::unique<Ts...>::value>>;
  };
};


}

#endif //TYPICAL_TYPICAL_HPP
