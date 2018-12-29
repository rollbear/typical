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


#include <typical/algorithms/front.hpp>
#include <typical/application.hpp>

using typical::apply_pack;
using typical::apply_pack_to;

static_assert(std::is_same_v<apply_pack<typical::front, void, int, char>, void>);
static_assert(std::is_same_v<apply_pack_to<typical::front, typical::make<std::tuple>, int, char, void>,
  std::tuple<int>>);
