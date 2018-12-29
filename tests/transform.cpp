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


#include <typical/algorithms/transform.hpp>
#include <typical/type_manipulation.hpp>
#include <typical/application.hpp>

using typical::apply_pack;

static_assert(std::is_same_v<apply_pack<typical::transform<typical::add_pointer>, int,char,double>,
              typical::list<int*,char*,double*>>);
static_assert(std::is_same_v<apply_pack<typical::transform<typical::add_pointer>>, typical::list<>>);
static_assert(std::is_same_v<apply_pack<typical::compose<typical::transform<typical::add_pointer>, typical::unwrap>, std::tuple<int,char,double>>, typical::list<int*,char*,double*>>);
