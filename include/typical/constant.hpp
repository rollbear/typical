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


#ifndef TYPICAL_CONSTANT_HPP
#define TYPICAL_CONSTANT_HPP

#include <type_traits>

namespace typical
{
template <typename T, T v>
struct typed_constant
{
  using type = T;
  static constexpr T value{v};
  constexpr operator type() const { return v;}
};

template<auto V>
using constant = typed_constant<std::remove_cv_t<decltype(V)>, V>;

template<auto V>
inline constexpr auto constant_v = constant<V>{};

template <typename T1, T1 v1, typename T2, T2 v2>
constexpr constant<(v1+v2)> operator+(typed_constant<T1,v1>,typed_constant<T2,v2>) { return {};}
template <typename T1, T1 v1, typename T2, T2 v2>
constexpr constant<(v1-v2)> operator-(typed_constant<T1,v1>,typed_constant<T2,v2>) { return {};}
template <typename T1, T1 v1, typename T2, T2 v2>
constexpr constant<(v1/v2)> operator/(typed_constant<T1,v1>,typed_constant<T2,v2>) { return {};}
template <typename T1, T1 v1, typename T2, T2 v2>
constexpr constant<(v1*v2)> operator*(typed_constant<T1,v1>,typed_constant<T2,v2>) { return {};}
template <typename T1, T1 v1, typename T2, T2 v2>
constexpr constant<(v1%v2)> operator%(typed_constant<T1,v1>,typed_constant<T2,v2>) { return {};}
template <typename T1, T1 v1, typename T2, T2 v2>
constexpr constant<(v1==v2)> operator==(typed_constant<T1,v1>,typed_constant<T2,v2>) { return {};}
template <typename T1, T1 v1, typename T2, T2 v2>
constexpr constant<(v1!=v2)> operator!=(typed_constant<T1,v1>,typed_constant<T2,v2>) { return {};}
template <typename T1, T1 v1, typename T2, T2 v2>
constexpr constant<(v1<v2)> operator<(typed_constant<T1,v1>,typed_constant<T2,v2>) { return {};}
template <typename T1, T1 v1, typename T2, T2 v2>
constexpr constant<(v1<=v2)> operator<=(typed_constant<T1,v1>,typed_constant<T2,v2>) { return {};}
template <typename T1, T1 v1, typename T2, T2 v2>
constexpr constant<(v1>v2)> operator>(typed_constant<T1,v1>,typed_constant<T2,v2>) { return {};}
template <typename T1, T1 v1, typename T2, T2 v2>
constexpr constant<(v1>=v2)> operator>=(typed_constant<T1,v1>,typed_constant<T2,v2>) { return {};}
template <typename T1, T1 v1, typename T2, T2 v2>
constexpr constant<(v1|v2)> operator|(typed_constant<T1,v1>,typed_constant<T2,v2>) { return {};}
template <typename T1, T1 v1, typename T2, T2 v2>
constexpr constant<(v1&v2)> operator&(typed_constant<T1,v1>,typed_constant<T2,v2>) { return {};}
template <typename T1, T1 v1, typename T2, T2 v2>
constexpr constant<(v1^v2)> operator^(typed_constant<T1,v1>,typed_constant<T2,v2>) { return {};}
template <typename T1, T1 v1, typename T2, T2 v2>
constexpr constant<(v1&&v2)> operator&&(typed_constant<T1,v1>,typed_constant<T2,v2>) { return {};}
template <typename T1, T1 v1, typename T2, T2 v2>
constexpr constant<(v1||v2)> operator||(typed_constant<T1,v1>,typed_constant<T2,v2>) { return {};}

template <typename T1, auto v1>
constexpr constant<!v1> operator!(typed_constant<T1,v1>) { return {};}
template <typename T1, T1 v1>
constexpr constant<(~v1)> operator~(typed_constant<T1,v1>) { return {};}

}

#endif //TYPICAL_CONSTANT_HPP
