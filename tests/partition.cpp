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

#include <typical/algorithms/partition.hpp>
#include <typical/type_predicates.hpp>

#include <tuple>

using typical::apply_pack;
using typical::apply_pack_to;

static_assert(std::is_same_v<apply_pack<typical::partition<typical::is_pointer>, int,void*,int*, double, char*>,
              typical::list<typical::list<void*,int*,char*>,typical::list<int,double>>>);
static_assert(std::is_same_v<apply_pack<typical::partition<typical::is_pointer>, int*,void*,int*, double*, char*>,
  typical::list<typical::list<int*,void*,int*,double*,char*>,typical::list<>>>);
static_assert(std::is_same_v<apply_pack<typical::partition<typical::is_pointer>, int,void,int, double, char>,
  typical::list<typical::list<>,typical::list<int,void,int, double, char>>>);
static_assert(std::is_same_v<apply_pack<typical::partition<typical::is_pointer>>,
  typical::list<typical::list<>,typical::list<>>>);
static_assert(std::is_same_v<apply_pack_to<typical::partition<typical::is_pointer>, typical::make<std::tuple>, int,void*,int*, double, char*>,
  std::tuple<typical::list<void*, int*, char*>,typical::list<int,double>>>);
