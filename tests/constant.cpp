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


#include <typical/constant.hpp>

static_assert(typical::constant_v<3> == 3);
static_assert(std::is_same_v<decltype(typical::constant_v<' '>), const typical::typed_constant<char, ' '>>);
static_assert(std::is_same_v<decltype(typical::constant<5>::value), const int>);

static_assert(std::is_same_v<decltype(typical::constant_v<15> + typical::constant_v<3U>), typical::constant<18U>>);
static_assert(std::is_same_v<decltype(typical::constant_v<15> - typical::constant_v<3U>), typical::constant<12U>>);
static_assert(std::is_same_v<decltype(typical::constant_v<15> / typical::constant_v<3U>), typical::constant<5U>>);
static_assert(std::is_same_v<decltype(typical::constant_v<15> * typical::constant_v<3U>), typical::constant<45U>>);
static_assert(std::is_same_v<decltype(typical::constant_v<15> % typical::constant_v<3U>), typical::constant<0U>>);
static_assert(std::is_same_v<decltype(typical::constant_v<15> == typical::constant_v<3U>), typical::constant<false>>);
static_assert(std::is_same_v<decltype(typical::constant_v<15> != typical::constant_v<3U>), typical::constant<true>>);
static_assert(std::is_same_v<decltype(typical::constant_v<15> < typical::constant_v<3U>), typical::constant<false>>);
static_assert(std::is_same_v<decltype(typical::constant_v<15> <= typical::constant_v<3U>), typical::constant<false>>);
static_assert(std::is_same_v<decltype(typical::constant_v<15> > typical::constant_v<3U>), typical::constant<true>>);
static_assert(std::is_same_v<decltype(typical::constant_v<15> >= typical::constant_v<3U>), typical::constant<true>>);
static_assert(std::is_same_v<decltype(typical::constant_v<15> == typical::constant_v<3U>), typical::constant<false>>);
static_assert(std::is_same_v<decltype(typical::constant_v<15> | typical::constant_v<3U>), typical::constant<15U>>);
static_assert(std::is_same_v<decltype(typical::constant_v<15> & typical::constant_v<3U>), typical::constant<3U>>);
static_assert(std::is_same_v<decltype(typical::constant_v<15> ^ typical::constant_v<3U>), typical::constant<12U>>);
static_assert(std::is_same_v<decltype(typical::constant_v<15> && typical::constant_v<3U>), typical::constant<true>>);
static_assert(std::is_same_v<decltype(typical::constant_v<15> || typical::constant_v<0U>), typical::constant<true>>);
static_assert(std::is_same_v<decltype(~typical::constant_v<15>), typical::constant<(~15)>>);
static_assert(std::is_same_v<decltype(!typical::constant_v<15>), typical::constant<false>>);

