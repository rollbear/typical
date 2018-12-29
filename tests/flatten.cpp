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


#include <typical/algorithms/flatten.hpp>

#include <variant>

template <auto>
class c;

using typical::apply_pack;
using typical::apply_pack_to;

static_assert(std::is_same_v<apply_pack<typical::flatten,
  typical::list<c<1>,c<2>,typical::list<c<3>, c<4>, typical::list<c<5>, c<6>>>,std::tuple<c<7>, c<8>, typical::list<c<9>,c<10>>>,typical::list<c<11>,typical::list<c<12>,typical::list<c<13>>>>>>,
typical::list<c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,std::tuple<c<7>,c<8>,typical::list<c<9>,c<10>>>,c<11>,c<12>,c<13>>>);


static_assert(std::is_same_v<apply_pack_to<typical::flatten, typical::make<std::tuple>,
  std::variant<int, std::variant<char,double>, void*>>,
  std::tuple<int,char,double,void*>>);
static_assert(std::is_same_v<apply_pack<typical::flatten,
  std::variant<int, std::variant<char,double>, void*>>,
  typical::list<int,char,double,void*>>);
