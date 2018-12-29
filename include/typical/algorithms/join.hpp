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


#ifndef TYPICAL_JOIN_HPP
#define TYPICAL_JOIN_HPP

#include <typical/utilities.hpp>
#include <typical/function_support.hpp>

namespace typical
{
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

}
#endif //TYPICAL_JOIN_HPP
