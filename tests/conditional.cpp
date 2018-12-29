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


#include <typical/conditional.hpp>

#include <type_traits>

static_assert(std::is_same_v<typical::conditional_t<true, void, char>, void>);
static_assert(std::is_same_v<typical::conditional_t<false, void, char>, char>);

