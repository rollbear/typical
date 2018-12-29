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


#include <typical/algorithms/count_if.hpp>

#include <typical/type_predicates.hpp>

using typical::apply_pack;
using typical::apply_pack_to;

static_assert(std::is_same_v<apply_pack<typical::count_if<typical::is_pointer>,int,int*,void*,double>,
              typical::constant<2>>);
static_assert(std::is_same_v<apply_pack<typical::count_if<typical::is_reference>,int,int*,void*,double>,
              typical::constant<0>>);
static_assert(std::is_same_v<apply_pack<typical::count_if<typical::is_same<int>>,int,int*,void*,double>,
              typical::constant<1>>);

static_assert(std::is_same_v<apply_pack<typical::count_if<typical::is_same<int>>>,
  typical::constant<0>>);

static_assert(std::is_same_v<apply_pack_to<typical::count_if<typical::is_same<int>>,typical::make<std::tuple>, int,int*,void*,double>,
  std::tuple<typical::constant<1>>>);
