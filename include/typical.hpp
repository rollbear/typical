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


#ifndef TYPICAL_TYPICAL_HPP
#define TYPICAL_TYPICAL_HPP

#include <typical/constant.hpp>
#include <typical/conditional.hpp>
#include <typical/function_support.hpp>
#include <typical/compose.hpp>
#include <typical/type_manipulation.hpp>
#include <typical/type_predicates.hpp>
#include <typical/list_predicates.hpp>
#include <typical/application.hpp>
#include <typical/algorithms/transform.hpp>
#include <typical/algorithms/join.hpp>
#include <typical/algorithms/size.hpp>
#include <typical/algorithms/filter.hpp>
#include <typical/algorithms/partition.hpp>
#include <typical/algorithms/drop_front.hpp>
#include <typical/algorithms/take.hpp>
#include <typical/algorithms/count_if.hpp>
#include <typical/algorithms/index_of.hpp>
#include <typical/algorithms/front.hpp>
#include <typical/algorithms/at.hpp>
#include <typical/algorithms/reverse.hpp>
#include <typical/algorithms/flatten.hpp>
#include <typical/algorithms/zip.hpp>
#include <typical/utilities.hpp>
#include <type_traits>
#include <utility>

namespace typical {

template<typename T>
using identity_t = apply_one<identity, T>;

template<typename T>
struct identity_template;

template<template<typename ...> class L, typename ... Ts>
struct identity_template<L<Ts...>> : make<L> {
};


}

#endif //TYPICAL_TYPICAL_HPP
