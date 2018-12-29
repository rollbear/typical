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


#include <typical/type_manipulation.hpp>
#include <variant>
template <typename>
struct wrapped;

struct wrap
{
  template <typename T>
  using result = wrapped<T>;
};

static_assert(std::is_same_v<typical::add_pointer::to<>::result<int>, int*>);
static_assert(std::is_same_v<typical::add_pointer::to<wrap>::result<int>, wrapped<int*>>);

static_assert(std::is_same_v<typical::add_lvalue_reference::to<>::result<int>, int&>);
static_assert(std::is_same_v<typical::add_lvalue_reference::to<wrap>::result<int>, wrapped<int&>>);

static_assert(std::is_same_v<typical::add_rvalue_reference::to<>::result<int>, int&&>);
static_assert(std::is_same_v<typical::add_rvalue_reference::to<wrap>::result<int>, wrapped<int&&>>);

static_assert(std::is_same_v<typical::add_const::to<>::result<int>, int const>);
static_assert(std::is_same_v<typical::add_const::to<wrap>::result<int>, wrapped<int const>>);

static_assert(std::is_same_v<typical::add_volatile::to<>::result<int>, int volatile>);
static_assert(std::is_same_v<typical::add_volatile::to<wrap>::result<int>, wrapped<int volatile>>);

static_assert(std::is_same_v<typical::remove_const::to<>::result<int const volatile>, int volatile>);
static_assert(std::is_same_v<typical::remove_const::to<wrap>::result<int const volatile>, wrapped<int volatile>>);

static_assert(std::is_same_v<typical::remove_volatile::to<>::result<int const volatile>, int const>);
static_assert(std::is_same_v<typical::remove_volatile::to<wrap>::result<int const volatile>, wrapped<int const>>);

static_assert(std::is_same_v<typical::remove_pointer::to<>::result<int const* volatile>, int const>);
static_assert(std::is_same_v<typical::remove_pointer::to<wrap>::result<int const* volatile>, wrapped<int const>>);
static_assert(std::is_same_v<typical::remove_pointer::to<>::result<int const>, int const>);

static_assert(std::is_same_v<typical::remove_reference::to<>::result<int const&>, int const>);
static_assert(std::is_same_v<typical::remove_reference::to<wrap>::result<int const&>, wrapped<int const>>);
static_assert(std::is_same_v<typical::remove_reference::to<>::result<int const>, int const>);

static_assert(std::is_same_v<typical::remove_cv::to<>::result<int>, int>);
static_assert(std::is_same_v<typical::remove_cv::to<wrap>::result<int>, wrapped<int>>);
static_assert(std::is_same_v<typical::remove_cv::to<>::result<int const>, int>);
static_assert(std::is_same_v<typical::remove_cv::to<>::result<int volatile>, int>);
static_assert(std::is_same_v<typical::remove_cv::to<>::result<int const volatile>, int>);
static_assert(std::is_same_v<typical::remove_cv::to<>::result<int const volatile&>, int const volatile&>);

static_assert(std::is_same_v<typical::remove_cv_ref::to<>::result<int>, int>);
static_assert(std::is_same_v<typical::remove_cv_ref::to<wrap>::result<int>, wrapped<int>>);
static_assert(std::is_same_v<typical::remove_cv_ref::to<>::result<int const>, int>);
static_assert(std::is_same_v<typical::remove_cv_ref::to<>::result<int const&>, int>);
static_assert(std::is_same_v<typical::remove_cv_ref::to<>::result<int const&&>, int>);
static_assert(std::is_same_v<typical::remove_cv_ref::to<>::result<int volatile>, int>);
static_assert(std::is_same_v<typical::remove_cv_ref::to<>::result<int volatile&>, int>);
static_assert(std::is_same_v<typical::remove_cv_ref::to<>::result<int volatile&&>, int>);
static_assert(std::is_same_v<typical::remove_cv_ref::to<>::result<int const volatile>, int>);
static_assert(std::is_same_v<typical::remove_cv_ref::to<>::result<int const volatile&>, int>);
static_assert(std::is_same_v<typical::remove_cv_ref::to<>::result<int const volatile&&>, int>);

static_assert(std::is_same_v<typical::metamorph_t<std::tuple<int,char,double>, std::variant>, std::variant<int,char,double>>);
static_assert(std::is_same_v<typical::metamorph_t<std::variant<>, std::tuple>, std::tuple<>>);
