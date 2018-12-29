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


#include <typical/function_support.hpp>

#include <tuple>

template <typename>
struct is_int
{
  static constexpr bool value = false;
};

template <>
struct is_int<int>
{
  static constexpr bool value = true;
};

template <typename T>
struct add_const
{
  using type = const T;
};

struct value_to_integral_constant
{
  template <typename T>
  using result = std::integral_constant<typename T::type, T::value>;
};

template <typename T>
struct wrapped {};

struct wrap
{
  template <typename T>
  using result = wrapped<T>;
};

static_assert(std::is_same_v<typical::bind_front<std::tuple, int, char>::result<unsigned, bool>,
  std::tuple<int,char,unsigned,bool>>);

static_assert(std::is_same_v<typical::from_value<is_int>::to<>::result<char>,
  typical::constant<false>>);
static_assert(std::is_same_v<typical::from_value<is_int>::to<>::result<int>,
  typical::constant<true>>);
static_assert(std::is_same_v<typical::from_value<is_int>::to<value_to_integral_constant>::result<char>,
  std::bool_constant<false>>);
static_assert(std::is_same_v<typical::from_value<is_int>::to<value_to_integral_constant>::result<int>,
  std::bool_constant<true>>);

static_assert(std::is_same_v<typical::from_type<add_const>::to<>::result<char>,
  const char>);
static_assert(std::is_same_v<typical::from_type<add_const>::to<wrap>::result<char>,
  wrapped<const char>>);
