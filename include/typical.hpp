#ifndef TYPICAL_TYPICAL_HPP
#define TYPICAL_TYPICAL_HPP

#include <type_traits>
#include <utility>
namespace typical {

static constexpr unsigned log2(unsigned n, unsigned b=16)
{
  if (n <= 1) return 0;
  const auto hm = ~((1U << b)-1U);
  return n & hm ? b+log2(n>>b, b>>1) : log2(n, b>>1);
}

template<typename...>
struct list {};

template<typename F, typename ... Ts>
using apply_pack = typename F::template result<Ts...>;

template <typename F, typename T>
using apply_one = typename F::template result<T>;

struct identity {
  template<typename T>
  using result = T;
};

template<typename T>
using identity_t = apply_one<identity, T>;

template<template<typename ...> class C>
struct make {
  template<typename ... T>
  using result = C<T...>;
};

template <template <typename ...> class, typename, typename>
struct make_n_;

template <template <typename ...> class C, typename T, std::size_t ... I>
struct make_n_<C, T, std::index_sequence<I...>>
{
  template <std::size_t>
  using made = T;
  using type = C<made<I>...>;
};

template <template <typename ...> class C, std::size_t N, typename T>
using make_n = typename make_n_<C, T, std::make_index_sequence<N>>::type;

template <template <typename> class F, template <typename> class ... Fs>
struct compose
{
  template <typename C = make<list>>
  struct function
  {
    template <typename ... Ts>
    using result = apply_pack<typename compose<Fs...>::template function<F<C>>, Ts...>;
  };
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
  using result = typename helper<Vs...>::type;
};

template<template<typename ...> class T, typename C = identity>
struct from_type {
  template <typename ... Vs>
  struct helper {
    using type = typename T<Vs...>::type;
  };
  template<typename ... Vs>
  using result = apply_one<C, typename helper<Vs...>::type>;
};

template <typename T, T v>
struct typed_constant
{
  using type = T;
  static constexpr T value{v};
};

template<auto V>
using constant = typed_constant<std::remove_cv_t<decltype(V)>, V>;

template<auto V>
inline constexpr auto constant_v = constant<V>::value;

template <template <typename ...> class T, typename C = identity>
struct from_value
{
  template <typename ... Vs>
  using result = apply_one<C, constant<T<Vs...>::value>>;
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
using is_same = from_type<bind_front<std::is_same, T>::template result, C>;

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
  using result = apply_pack<C, constant<is_template_t<T, U>::value>>;
};

template<typename F, typename C = identity>
struct negate {
  template<typename ...Ts>
  using result = apply_pack<C, constant<!apply_pack<F, Ts...>::value>>;
};


template <typename C = identity>
using remove_cv = compose<remove_volatile,remove_const>::function<C>;

template <typename C = identity>
using remove_cv_ref = compose<remove_cv, remove_reference>::function<C>;

template<typename F, typename C = make<list>>
struct transform {
  template<typename ... Ts>
  using result = apply_pack<C, apply_one<F,Ts>...>;
};

template <typename C = make<list>>
struct unwrap {
  template <typename T>
  struct helper
  {
    using type = apply_one<C, T>;
  };
  template <template <typename ...> class L, typename... Ts>
  struct helper<L<Ts...>>
  {
    using type = apply_pack<C, Ts...>;
  };
  template <typename ...Ts>
  using result = typename helper<Ts...>::type;
};


template <template <typename> class F>
struct compose<F>
{
  template <typename C = make<list>>
  struct function
  {
    template <typename ... Ts>
    using result = apply_pack<F<C>, Ts...>;
  };
};


template <template <typename ...> class C>
struct metamorph
{
  template <typename ... Ts>
  using result = apply_pack<unwrap<make<C>>, Ts...>;
};

template<typename L, template<typename ...> class D>
using metamorph_t = apply_pack<metamorph<D>, L>;


template <typename C = make<list>>
struct concat
{
  template <int N, typename ...Ts>
  struct helper
  {
    using type = apply_pack<C>;
  };

  template <template <typename...> class L, typename ... Ts>
  struct helper<0, L<Ts...>>
  {
    using type = apply_pack<C, Ts...>;
  };
  template <template <typename...> class L, typename ...T1s, typename ... T2s>
  struct helper<0, L<T1s...>,L<T2s...>>
  {
    using type = apply_pack<C, T1s...,T2s...>;
  };
  template <template<typename...> class L, typename ...T1s, typename ...T2s, typename ... Tail>
  struct helper<1, L<T1s...>, L<T2s...>, Tail...>
  {
    using type = typename helper<log2(sizeof...(Tail)+1), L<T1s...,T2s...>, Tail...>::type;
  };
  template <template<typename...> class L, typename ...T1s, typename ...T2s, typename ...T3s, typename ...T4s, typename ... Tail>
  struct helper<2, L<T1s...>, L<T2s...>, L<T3s...>, L<T4s...>, Tail...>
  {
    using type = typename helper<log2(sizeof...(Tail)+1), L<T1s...,T2s...,T3s..., T4s...>, Tail...>::type;
  };
  template <template<typename...> class L, typename ...T1s, typename ...T2s, typename ...T3s, typename ...T4s,
    typename ...T5s, typename ...T6s,typename...T7s,typename ...T8s,typename ... Tail>
  struct helper<3, L<T1s...>, L<T2s...>, L<T3s...>, L<T4s...>,L<T5s...>,L<T6s...>,L<T7s...>,L<T8s...>,
    Tail...>
  {
    using type = typename helper<log2(sizeof...(Tail)+1), L<T1s...,T2s...,T3s..., T4s...,T5s...,T6s...,T7s...,T8s...>, Tail...>::type;
  };
  template <template<typename...> class L,
    typename ...T1s, typename ...T2s, typename ...T3s, typename ...T4s,
    typename ...T5s, typename ...T6s, typename... T7s, typename ...T8s,
    typename ...T9s, typename ...T10s,typename...T11s, typename ...T12s,
    typename ...T13s,typename ...T14s,typename...T15s, typename ...T16s,typename ... Tail>
  struct helper<4, L<T1s...>, L<T2s...>, L<T3s...>, L<T4s...>,L<T5s...>,L<T6s...>,L<T7s...>,L<T8s...>,
    L<T9s...>,L<T10s...>,L<T11s...>,L<T12s...>,L<T13s...>,L<T14s...>,L<T15s...>,L<T16s...>,
    Tail...>
  {
    using type = typename helper<log2(sizeof...(Tail)+1), L<T1s...,T2s...,T3s..., T4s...,T5s...,T6s...,T7s...,T8s...,T9s...,T10s...,T11s...,T12s...,T13s...,T14s...,T15s...,T16s...>, Tail...>::type;
  };
  template <template<typename...> class L,
    typename ...T1s, typename ...T2s, typename ...T3s, typename ...T4s,
    typename ...T5s, typename ...T6s, typename... T7s, typename ...T8s,
    typename ...T9s, typename ...T10s,typename...T11s, typename ...T12s,
    typename ...T13s,typename ...T14s,typename...T15s, typename ...T16s,
    typename ...T17s,typename ...T18s,typename...T19s, typename ...T20s,
    typename ...T21s,typename ...T22s,typename...T23s, typename ...T24s,
    typename ...T25s,typename ...T26s,typename...T27s, typename ...T28s,
    typename ...T29s,typename ...T30s,typename...T31s, typename ...T32s,
    typename ... Tail>
  struct helper<5, L<T1s...>, L<T2s...>, L<T3s...>, L<T4s...>,L<T5s...>,L<T6s...>,L<T7s...>,L<T8s...>,
    L<T9s...>,L<T10s...>,L<T11s...>,L<T12s...>,L<T13s...>,L<T14s...>,L<T15s...>,L<T16s...>,
    L<T17s...>,L<T18s...>,L<T19s...>,L<T20s...>,L<T21s...>,L<T22s...>,L<T23s...>,L<T24s...>,
    L<T25s...>,L<T26s...>,L<T27s...>,L<T28s...>,L<T29s...>,L<T30s...>,L<T31s...>,L<T32s...>,
    Tail...>
  {
    using type = typename helper<log2(sizeof...(Tail)+1), L<T1s...,T2s...,T3s..., T4s...,T5s...,T6s...,T7s...,T8s...,T9s...,T10s...,T11s...,T12s...,T13s...,T14s...,T15s...,T16s...,T17s...,T18s...,T19s...,T20s...,T21s...,T22s...,T23s...,T24s...,T25s...,T26s...,T27s...,T28s...,T29s...,T30s...,T31s...,T32s...>, Tail...>::type;
  };
  template <template<typename...> class L,
    typename ...T1s, typename ...T2s, typename ...T3s, typename ...T4s,
    typename ...T5s, typename ...T6s, typename... T7s, typename ...T8s,
    typename ...T9s, typename ...T10s,typename...T11s, typename ...T12s,
    typename ...T13s,typename ...T14s,typename...T15s, typename ...T16s,
    typename ...T17s,typename ...T18s,typename...T19s, typename ...T20s,
    typename ...T21s,typename ...T22s,typename...T23s, typename ...T24s,
    typename ...T25s,typename ...T26s,typename...T27s, typename ...T28s,
    typename ...T29s,typename ...T30s,typename...T31s, typename ...T32s,
    typename ...T33s,typename ...T34s,typename...T35s, typename ...T36s,
    typename ...T37s,typename ...T38s,typename...T39s, typename ...T40s,
    typename ...T41s,typename ...T42s,typename...T43s, typename ...T44s,
    typename ...T45s,typename ...T46s,typename...T47s, typename ...T48s,
    typename ...T49s,typename ...T50s,typename...T51s, typename ...T52s,
    typename ...T53s,typename ...T54s,typename...T55s, typename ...T56s,
    typename ...T57s,typename ...T58s,typename ...T59s,typename ...T60s,
    typename ...T61s,typename ...T62s,typename ...T63s,typename ...T64s,
    typename ... Tail>
  struct helper<6, L<T1s...>, L<T2s...>, L<T3s...>, L<T4s...>,L<T5s...>,L<T6s...>,L<T7s...>,L<T8s...>,
    L<T9s...>,L<T10s...>,L<T11s...>,L<T12s...>,L<T13s...>,L<T14s...>,L<T15s...>,L<T16s...>,
    L<T17s...>,L<T18s...>,L<T19s...>,L<T20s...>,L<T21s...>,L<T22s...>,L<T23s...>,L<T24s...>,
    L<T25s...>,L<T26s...>,L<T27s...>,L<T28s...>,L<T29s...>,L<T30s...>,L<T31s...>,L<T32s...>,
    L<T33s...>,L<T34s...>,L<T35s...>,L<T36s...>,L<T37s...>,L<T38s...>,L<T39s...>,L<T40s...>,
    L<T41s...>,L<T42s...>,L<T43s...>,L<T44s...>,L<T45s...>,L<T46s...>,L<T47s...>,L<T48s...>,
    L<T49s...>,L<T50s...>,L<T51s...>,L<T52s...>,L<T53s...>,L<T54s...>,L<T55s...>,L<T56s...>,
    L<T57s...>,L<T58s...>,L<T59s...>,L<T60s...>,L<T61s...>,L<T62s...>,L<T63s...>,L<T64s...>,
    Tail...>
  {
    using type = typename helper<log2(sizeof...(Tail)+1), L<T1s...,T2s...,T3s..., T4s...,T5s...,T6s...,T7s...,T8s...,T9s...,T10s...,T11s...,T12s...,T13s...,T14s...,T15s...,T16s...,T17s...,T18s...,T19s...,T20s...,T21s...,T22s...,T23s...,T24s...,T25s...,T26s...,T27s...,T28s...,T29s...,T30s...,T31s...,T32s...,T33s...,T34s...,T35s...,T36s...,T37s...,T38s...,T39s...,T40s...,T41s...,T42s...,T43s...,T44s...,T45s...,T46s...,T47s...,T48s...,T49s...,T50s...,T51s...,T52s...,T53s...,T54s...,T50s...,T51s...,T52s...,T53s...,T54s...,T55s...,T56s...,T57s...,T58s...,T59s...,T60s...,T61s...,T62s...,T63s...,T64s...>, Tail...>::type;
  };
  template <int N, template<typename...> class L,
    typename ...T1s,  typename ...T2s,  typename ... T3s, typename ...T4s,
    typename ...T5s,  typename ...T6s,  typename ... T7s, typename ...T8s,
    typename ...T9s,  typename ...T10s, typename ...T11s, typename ...T12s,
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
    typename ...T101s,typename ...T102s,typename ...T103s,typename ...T104s,
    typename ...T105s,typename ...T106s,typename ...T107s,typename ...T108s,
    typename ...T109s,typename ...T110s,typename ...T111s,typename ...T112s,
    typename ...T113s,typename ...T114s,typename ...T115s,typename ...T116s,
    typename ...T117s,typename ...T118s,typename ...T119s,typename ...T120s,
    typename ...T121s,typename ...T122s,typename ...T123s,typename ...T124s,
    typename ...T125s,typename ...T126s,typename ...T127s,typename ...T128s,
    typename ... Tail>
  struct helper<N, L<T1s...>, L<T2s...>, L<T3s...>, L<T4s...>,L<T5s...>,L<T6s...>,L<T7s...>,L<T8s...>,
    L<T9s...>,L<T10s...>,L<T11s...>,L<T12s...>,L<T13s...>,L<T14s...>,L<T15s...>,L<T16s...>,
    L<T17s...>,L<T18s...>,L<T19s...>,L<T20s...>,L<T21s...>,L<T22s...>,L<T23s...>,L<T24s...>,
    L<T25s...>,L<T26s...>,L<T27s...>,L<T28s...>,L<T29s...>,L<T30s...>,L<T31s...>,L<T32s...>,
    L<T33s...>,L<T34s...>,L<T35s...>,L<T36s...>,L<T37s...>,L<T38s...>,L<T39s...>,L<T40s...>,
    L<T41s...>,L<T42s...>,L<T43s...>,L<T44s...>,L<T45s...>,L<T46s...>,L<T47s...>,L<T48s...>,
    L<T49s...>,L<T50s...>,L<T51s...>,L<T52s...>,L<T53s...>,L<T54s...>,L<T55s...>,L<T56s...>,
    L<T57s...>,L<T58s...>,L<T59s...>,L<T60s...>,L<T61s...>,L<T62s...>,L<T63s...>,L<T64s...>,
    L<T64s...>,L<T65s...>,L<T66s...>,L<T67s...>,L<T68s...>,L<T69s...>,L<T70s...>,L<T71s...>,
    L<T72s...>,L<T73s...>,L<T74s...>,L<T75s...>,L<T76s...>,L<T77s...>,L<T78s...>,L<T79s...>,
    L<T80s...>,L<T81s...>,L<T82s...>,L<T83s...>,L<T84s...>,L<T85s...>,L<T86s...>,L<T87s...>,
    L<T88s...>,L<T89s...>,L<T90s...>,L<T91s...>,L<T92s...>,L<T93s...>,L<T94s...>,L<T95s...>,
    L<T96s...>,L<T97s...>,L<T98s...>,L<T99s...>,L<T100s...>,L<T101s...>,L<T102s...>,L<T103s...>,
    L<T104s...>,L<T105s...>,L<T106s...>,L<T107s...>,L<T108s...>,L<T109s...>,L<T110s...>,L<T111s...>,
    L<T112s...>,L<T113s...>,L<T114s...>,L<T115s...>,L<T116s...>,L<T117s...>,L<T118s...>,L<T119s...>,
    L<T120s...>,L<T121s...>,L<T122s...>,L<T123s...>,L<T124s...>,L<T125s...>,L<T126s...>,L<T127s...>,
    L<T128s...>,Tail...>
  {
    using type = typename helper<log2(sizeof...(Tail)+1), L<T1s...,T2s...,T3s..., T4s...,T5s...,T6s...,T7s...,T8s...,T9s...,T10s...,T11s...,T12s...,T13s...,T14s...,T15s...,T16s...,T17s...,T18s...,T19s...,T20s...,T21s...,T22s...,T23s...,T24s...,T25s...,T26s...,T27s...,T28s...,T29s...,T30s...,T31s...,T32s...,T33s...,T34s...,T35s...,T36s...,T37s...,T38s...,T39s...,T40s...,T41s...,T42s...,T43s...,T44s...,T45s...,T46s...,T47s...,T48s...,T49s...,T50s...,T51s...,T52s...,T53s...,T54s...,T50s...,T51s...,T52s...,T53s...,T54s...,T55s...,T56s...,T57s...,T58s...,T59s...,T60s...,T61s...,T62s...,T63s...,T64s...,T65s...,T66s...,T67s...,T68s...,T69s...,T70s...,T71s...,T72s...,T73s...,T74s...,T75s...,T76s...,T77s...,T78s...,T79s...,T80s...,T81s...,T82s...,T83s...,T84s...,T85s...,T86s...,T87s...,T88s...,T89s...,T90s...,T91s...,T92s...,T93s...,T94s...,T95s...,T96s...,T97s...,T98s...,T99s...,T100s...,T101s...,T102s...,T103s...,T104s...,T105s...,T106s...,T107s...,T108s...,T109s...,T110s...,T111s...,T112s...,T113s...,T114s...,T115s...,T116s...,T117s...,T118s...,T119s...,T120s...,T121s...,T122s...,T123s...,T124s...,T125s...,T126s...,T127s...,T128s...>, Tail...>::type;
  };
  template <typename ... Ts>
  using result = typename helper<log2(sizeof...(Ts)), Ts...>::type;
};

struct size {
  template<typename>
  struct helper;
  template<template<typename ...> class L, typename ... Ts>
  struct helper<L<Ts...>> {
    static constexpr std::size_t value = sizeof...(Ts);
  };
  template<typename T>
  using result = constant<helper<T>::value>;
};


template<typename F, typename C = make<list>>
struct zip {
  template<typename L1, typename L2>
  struct helper;
  template<template<typename ...> class L1, typename ... L1s,
    template<typename...> class L2, typename ... L2s>
  struct helper<L1<L1s...>, L2<L2s...>> {
    using type = apply_pack<C, apply_pack<F, L1s, L2s>...>;
  };
  template<typename L1, typename L2>
  using result = typename helper<L1, L2>::type;
};

template<typename L1, typename L2, typename F, typename C = make<list>>
using zip_t = apply_pack<zip<F, C>, L1, L2>;


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
using conditional_t = apply_pack<conditional<b>, T, U>;

template<typename P, typename C = make<list>>
struct filter
{
  template <typename ... Ts>
  using result = apply_pack<concat<C>, conditional_t<apply_one<P,Ts>::value,list<Ts>, list<>>...>;
};



template<typename P, typename L>
using filter_t = apply_pack<filter<P>, L>;

template <typename T>
struct wrapped;

template <typename N, typename C = make<list>>
struct drop_first
{
    template <typename>
    struct drop_first_;
    template <typename ... V>
    struct drop_first_<list<V...>>
    {
       template <typename ... T>
       static apply_pack<C, T...> func(V..., wrapped<T>*...);
    };
    template <typename ... Ts>
    using result = decltype(drop_first_<make_n<list, N::value, const void*>>::func(static_cast<wrapped<Ts>*>(nullptr)...));
};


template<typename P, typename C = make<list>>
struct partition {
  template <typename ... Ts>
  struct helper
  {
    using type = apply_pack<C, apply_pack<concat<make<list>>,conditional_t<apply_pack<P, Ts>::value, list<Ts>, list<>>...>,
      apply_pack<concat<make<list>>, conditional_t<apply_pack<P, Ts>::value, list<>, list<Ts>>...>>;
  };
  template<typename ... Ts>
  using result = typename helper<Ts...>::type;
};



template <typename C = identity>
struct front {
  template <typename T>
  static apply_one<C, T> func(wrapped<T>*,...);
  template <typename ... T>
  using result = decltype(func(static_cast<wrapped<T>*>(nullptr)...));
};


template<typename P, typename C = identity>
struct count_if {
  template <typename T>
  using eval = apply_one<P, T>;
  template<typename ...T>
  using result = apply_pack<C, constant<(eval<T>::value + ... + 0)>>;
};

template<typename P, typename L, typename C = identity>
using count_if_t = apply_pack<count_if<P>, L, C>;

template<typename P, typename L>
constexpr inline auto count_if_v = count_if_t<P, L>::value;


template<typename P, typename C = identity>
struct any_of {
  template<typename ...Ts>
  using result = apply_pack<C, constant<std::disjunction_v<apply_one<P,Ts>...>>>;
};

template<typename P, typename C = identity>
struct all_of {
  template<typename ... Ts>
  using result = apply_pack<C, constant<std::conjunction_v<apply_one<P,Ts>...>>>;
};

template<typename P, typename C = identity>
using none_of = negate<any_of<P>, C>;



template <typename N, typename C = identity>
struct nth_type
{
  template <typename ...Ts>
  using result = apply_pack<drop_first<N, front<C>>, Ts...>;
};

template <typename C>
struct nth_type<constant<0>, C>
{
  template <typename T, typename ...>
  using result = apply_one<C, T>;
};

template<typename C = make<list>>
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
    using type = apply_pack<concat<C>, typename helper<N-10, L<Ts...>>::type, L<T10, T9, T8, T7, T6, T5, T4, T3, T2, T1>>;
  };
  template <typename ...T>
  using result = typename helper<sizeof...(T), apply_pack<C,T...>>::type;
};

template <typename C = make<list>>
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
      using type = apply_pack<concat<C>,typename split<Vs>::type...>;
    };
    using type = apply_pack<concat<C>, typename split<Ts>::type...>;
  };
  template <typename T>
  using result = typename helper<T>::type;
};

}

#endif //TYPICAL_TYPICAL_HPP
