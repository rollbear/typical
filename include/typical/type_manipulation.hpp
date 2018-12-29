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


#ifndef TYPICAL_TYPE_TRAITS_HPP
#define TYPICAL_TYPE_TRAITS_HPP

#include <typical/function_support.hpp>
#include <typical/compose.hpp>
#include <typical/application.hpp>
namespace typical
{
using add_pointer = from_type<std::add_pointer>;
using add_lvalue_reference = from_type<std::add_lvalue_reference>;
using add_rvalue_reference = from_type<std::add_rvalue_reference>;
using add_const = from_type<std::add_const>;
using add_volatile = from_type<std::add_volatile>;
using remove_reference = from_type<std::remove_reference>;
using remove_pointer = from_type<std::remove_pointer>;
using remove_const = from_type<std::remove_const>;
using remove_volatile = from_type<std::remove_volatile>;
using remove_cv = compose<remove_volatile,remove_const>;
using remove_cv_ref = compose<remove_cv, remove_reference>;

template <template <typename ...> class C>
struct metamorph
{
  template <typename ... Ts>
  using result = apply_pack_to<unwrap, make<C>, Ts...>;
};

template<typename L, template<typename ...> class D>
using metamorph_t = apply_one<metamorph<D>, L>;

}
#endif //TYPICAL_TYPE_TRAITS_HPP
