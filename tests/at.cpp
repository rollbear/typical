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


#include <typical/algorithms/at.hpp>

template <auto>
class c;

using typical::apply_pack;
using typical::apply_pack_to;

static_assert(std::is_same_v<apply_pack<typical::at<typical::constant<0>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
              c<1>>);
static_assert(std::is_same_v<apply_pack<typical::at<typical::constant<1>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
              c<2>>);
static_assert(std::is_same_v<apply_pack<typical::at<typical::constant<2>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
              c<3>>);
static_assert(std::is_same_v<apply_pack<typical::at<typical::constant<3>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
              c<4>>);
static_assert(std::is_same_v<apply_pack<typical::at<typical::constant<4>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
              c<5>>);
static_assert(std::is_same_v<apply_pack<typical::at<typical::constant<5>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
              c<6>>);
static_assert(std::is_same_v<apply_pack<typical::at<typical::constant<6>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
              c<7>>);
static_assert(std::is_same_v<apply_pack<typical::at<typical::constant<7>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
              c<8>>);
static_assert(std::is_same_v<apply_pack<typical::at<typical::constant<8>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
              c<9>>);
static_assert(std::is_same_v<apply_pack<typical::at<typical::constant<9>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
              c<10>>);
static_assert(std::is_same_v<apply_pack<typical::at<typical::constant<10>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
              c<11>>);
static_assert(std::is_same_v<apply_pack<typical::at<typical::constant<11>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
              c<12>>);
static_assert(std::is_same_v<apply_pack<typical::at<typical::constant<12>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
              c<13>>);
static_assert(std::is_same_v<apply_pack<typical::at<typical::constant<13>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
              c<14>>);
static_assert(std::is_same_v<apply_pack<typical::at<typical::constant<14>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
              c<15>>);
static_assert(std::is_same_v<apply_pack<typical::at<typical::constant<15>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
              c<16>>);
static_assert(std::is_same_v<apply_pack<typical::at<typical::constant<16>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
              c<17>>);
static_assert(std::is_same_v<apply_pack<typical::at<typical::constant<17>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
              c<18>>);
static_assert(std::is_same_v<apply_pack<typical::at<typical::constant<18>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
              c<19>>);
static_assert(std::is_same_v<apply_pack<typical::at<typical::constant<19>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
              c<20>>);
static_assert(std::is_same_v<apply_pack<typical::at<typical::constant<20>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
              c<21>>);
static_assert(std::is_same_v<apply_pack<typical::at<typical::constant<21>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
              c<22>>);
static_assert(std::is_same_v<apply_pack<typical::at<typical::constant<22>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
              c<23>>);
static_assert(std::is_same_v<apply_pack<typical::at<typical::constant<23>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
              c<24>>);
static_assert(std::is_same_v<apply_pack<typical::at<typical::constant<24>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
              c<25>>);
static_assert(std::is_same_v<apply_pack<typical::at<typical::constant<25>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
              c<26>>);
static_assert(std::is_same_v<apply_pack<typical::at<typical::constant<26>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
              c<27>>);
static_assert(std::is_same_v<apply_pack<typical::at<typical::constant<27>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
              c<28>>);
static_assert(std::is_same_v<apply_pack<typical::at<typical::constant<28>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
              c<29>>);
static_assert(std::is_same_v<apply_pack<typical::at<typical::constant<29>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
              c<30>>);
static_assert(std::is_same_v<apply_pack<typical::at<typical::constant<30>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
              c<31>>);
static_assert(std::is_same_v<apply_pack<typical::at<typical::constant<31>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
              c<32>>);
static_assert(std::is_same_v<apply_pack<typical::at<typical::constant<32>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
              c<33>>);
static_assert(std::is_same_v<apply_pack<typical::at<typical::constant<33>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
              c<34>>);
static_assert(std::is_same_v<apply_pack<typical::at<typical::constant<34>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
              c<35>>);

static_assert(std::is_same_v<apply_pack_to<typical::at<typical::constant<1>>, typical::make<std::tuple>, int, char, void, double>,
  std::tuple<char>>);
