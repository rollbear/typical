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


#include <typical/algorithms/join.hpp>
#include <typical/application.hpp>

#include <variant>

using typical::apply_pack;

template <typename ... Ts>
using L = typical::list<Ts...>;

template <auto N>
struct c {};

static_assert(std::is_same_v<apply_pack<typical::join>, L<>>);
static_assert(std::is_same_v<apply_pack<typical::join, L<c<1>>>, L<c<1>>>);
static_assert(std::is_same_v<apply_pack<typical::join, L<c<1>>,L<c<2>>>, L<c<1>,c<2>>>);
static_assert(std::is_same_v<apply_pack<typical::join, L<c<1>>,L<c<2>>,L<c<3>>>, L<c<1>,c<2>,c<3>>>);
static_assert(std::is_same_v<apply_pack<typical::join, L<c<1>>,L<c<2>>,L<c<3>>,L<c<4>>>,
L<c<1>,c<2>,c<3>,c<4>>>);
static_assert(std::is_same_v<apply_pack<typical::join, L<c<1>>,L<c<2>>,L<c<3>>,L<c<4>>,L<c<5>>>,
L<c<1>,c<2>,c<3>,c<4>,c<5>>>);
static_assert(std::is_same_v<apply_pack<typical::join, L<c<1>>,L<c<2>>,L<c<3>>,L<c<4>>,L<c<5>>,L<c<6>>>,
L<c<1>,c<2>,c<3>,c<4>,c<5>,c<6>>>);
static_assert(std::is_same_v<apply_pack<typical::join, L<c<1>>,L<c<2>>,L<c<3>>,L<c<4>>,L<c<5>>,L<c<6>>, L<c<7>>>,
L<c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>>>);
static_assert(std::is_same_v<apply_pack<typical::join, L<c<1>>,L<c<2>>,L<c<3>>,L<c<4>>,L<c<5>>,L<c<6>>, L<c<7>>,L<c<8>>>,
L<c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>>>);
static_assert(std::is_same_v<apply_pack<typical::join, L<c<1>>,L<c<2>>,L<c<3>>,L<c<4>>,L<c<5>>,L<c<6>>, L<c<7>>,L<c<8>>,L<c<9>>>,
L<c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>>>);
static_assert(std::is_same_v<apply_pack<typical::join, L<c<1>>,L<c<2>>,L<c<3>>,L<c<4>>,L<c<5>>,L<c<6>>, L<c<7>>,L<c<8>>,L<c<9>>,L<c<10>>>,
L<c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>>>);
static_assert(std::is_same_v<apply_pack<typical::join, L<c<1>>,L<c<2>>,L<c<3>>,L<c<4>>,L<c<5>>,L<c<6>>, L<c<7>>,L<c<8>>,L<c<9>>,L<c<10>>,L<c<11>>>,
L<c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>>>);
static_assert(std::is_same_v<apply_pack<typical::join, L<c<1>>,L<c<2>>,L<c<3>>,L<c<4>>,L<c<5>>,L<c<6>>, L<c<7>>,L<c<8>>,L<c<9>>,L<c<10>>,L<c<11>>,L<c<12>>>,
L<c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>>>);
static_assert(std::is_same_v<apply_pack<typical::join, L<c<1>>,L<c<2>>,L<c<3>>,L<c<4>>,L<c<5>>,L<c<6>>, L<c<7>>,L<c<8>>,L<c<9>>,L<c<10>>,L<c<11>>,L<c<12>>,L<c<13>>>,
L<c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>>>);
static_assert(std::is_same_v<apply_pack<typical::join, L<c<1>>,L<c<2>>,L<c<3>>,L<c<4>>,L<c<5>>,L<c<6>>, L<c<7>>,L<c<8>>,L<c<9>>,L<c<10>>,L<c<11>>,L<c<12>>,L<c<13>>,L<c<14>>>,
L<c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>>>);
static_assert(std::is_same_v<apply_pack<typical::join, L<c<1>>,L<c<2>>,L<c<3>>,L<c<4>>,L<c<5>>,L<c<6>>, L<c<7>>,L<c<8>>,L<c<9>>,L<c<10>>,L<c<11>>,L<c<12>>,L<c<13>>,L<c<14>>,L<c<15>>>,
L<c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>>>);
static_assert(std::is_same_v<apply_pack<typical::join, L<c<1>>,L<c<2>>,L<c<3>>,L<c<4>>,L<c<5>>,L<c<6>>, L<c<7>>,L<c<8>>,L<c<9>>,L<c<10>>,L<c<11>>,L<c<12>>,L<c<13>>,L<c<14>>,L<c<15>>,L<c<16>>>,
L<c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>>>);
static_assert(std::is_same_v<apply_pack<typical::join, L<c<1>>,L<c<2>>,L<c<3>>,L<c<4>>,L<c<5>>,L<c<6>>, L<c<7>>,L<c<8>>,L<c<9>>,L<c<10>>,L<c<11>>,L<c<12>>,L<c<13>>,L<c<14>>,L<c<15>>,L<c<16>>,L<c<17>>>,
L<c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>>>);
static_assert(std::is_same_v<apply_pack<typical::join, L<c<1>>,L<c<2>>,L<c<3>>,L<c<4>>,L<c<5>>,L<c<6>>, L<c<7>>,L<c<8>>,L<c<9>>,L<c<10>>,L<c<11>>,L<c<12>>,L<c<13>>,L<c<14>>,L<c<15>>,L<c<16>>,L<c<17>>,L<c<18>>>,
L<c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>>>);
static_assert(std::is_same_v<apply_pack<typical::join, L<c<1>>,L<c<2>>,L<c<3>>,L<c<4>>,L<c<5>>,L<c<6>>, L<c<7>>,L<c<8>>,L<c<9>>,L<c<10>>,L<c<11>>,L<c<12>>,L<c<13>>,L<c<14>>,L<c<15>>,L<c<16>>,L<c<17>>,L<c<18>>,L<c<19>>>,
L<c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>>>);
static_assert(std::is_same_v<apply_pack<typical::join, L<c<1>>,L<c<2>>,L<c<3>>,L<c<4>>,L<c<5>>,L<c<6>>, L<c<7>>,L<c<8>>,L<c<9>>,L<c<10>>,L<c<11>>,L<c<12>>,L<c<13>>,L<c<14>>,L<c<15>>,L<c<16>>,L<c<17>>,L<c<18>>,L<c<19>>,L<c<20>>>,
L<c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>>>);
static_assert(std::is_same_v<apply_pack<typical::join, L<c<1>>,L<c<2>>,L<c<3>>,L<c<4>>,L<c<5>>,L<c<6>>, L<c<7>>,L<c<8>>,L<c<9>>,L<c<10>>,L<c<11>>,L<c<12>>,L<c<13>>,L<c<14>>,L<c<15>>,L<c<16>>,L<c<17>>,L<c<18>>,L<c<19>>,L<c<20>>,L<c<21>>>,
L<c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>>>);
static_assert(std::is_same_v<apply_pack<typical::join, L<c<1>>,L<c<2>>,L<c<3>>,L<c<4>>,L<c<5>>,L<c<6>>, L<c<7>>,L<c<8>>,L<c<9>>,L<c<10>>,L<c<11>>,L<c<12>>,L<c<13>>,L<c<14>>,L<c<15>>,L<c<16>>,L<c<17>>,L<c<18>>,L<c<19>>,L<c<20>>,L<c<21>>,L<c<22>>>,
L<c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>>>);
static_assert(std::is_same_v<apply_pack<typical::join, L<c<1>>,L<c<2>>,L<c<3>>,L<c<4>>,L<c<5>>,L<c<6>>, L<c<7>>,L<c<8>>,L<c<9>>,L<c<10>>,L<c<11>>,L<c<12>>,L<c<13>>,L<c<14>>,L<c<15>>,L<c<16>>,L<c<17>>,L<c<18>>,L<c<19>>,L<c<20>>,L<c<21>>,L<c<22>>,L<c<23>>>,
L<c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>>>);
static_assert(std::is_same_v<apply_pack<typical::join, L<c<1>>,L<c<2>>,L<c<3>>,L<c<4>>,L<c<5>>,L<c<6>>, L<c<7>>,L<c<8>>,L<c<9>>,L<c<10>>,L<c<11>>,L<c<12>>,L<c<13>>,L<c<14>>,L<c<15>>,L<c<16>>,L<c<17>>,L<c<18>>,L<c<19>>,L<c<20>>,L<c<21>>,L<c<22>>,L<c<23>>,L<c<24>>>,
L<c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>>>);
static_assert(std::is_same_v<apply_pack<typical::join, L<c<1>>,L<c<2>>,L<c<3>>,L<c<4>>,L<c<5>>,L<c<6>>, L<c<7>>,L<c<8>>,L<c<9>>,L<c<10>>,L<c<11>>,L<c<12>>,L<c<13>>,L<c<14>>,L<c<15>>,L<c<16>>,L<c<17>>,L<c<18>>,L<c<19>>,L<c<20>>,L<c<21>>,L<c<22>>,L<c<23>>,L<c<24>>,L<c<25>>>,
L<c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>>>);
static_assert(std::is_same_v<apply_pack<typical::join, L<c<1>>,L<c<2>>,L<c<3>>,L<c<4>>,L<c<5>>,L<c<6>>, L<c<7>>,L<c<8>>,L<c<9>>,L<c<10>>,L<c<11>>,L<c<12>>,L<c<13>>,L<c<14>>,L<c<15>>,L<c<16>>,L<c<17>>,L<c<18>>,L<c<19>>,L<c<20>>,L<c<21>>,L<c<22>>,L<c<23>>,L<c<24>>,L<c<25>>,L<c<26>>>,
L<c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>>>);
static_assert(std::is_same_v<apply_pack<typical::join, L<c<1>>,L<c<2>>,L<c<3>>,L<c<4>>,L<c<5>>,L<c<6>>, L<c<7>>,L<c<8>>,L<c<9>>,L<c<10>>,L<c<11>>,L<c<12>>,L<c<13>>,L<c<14>>,L<c<15>>,L<c<16>>,L<c<17>>,L<c<18>>,L<c<19>>,L<c<20>>,L<c<21>>,L<c<22>>,L<c<23>>,L<c<24>>,L<c<25>>,L<c<26>>,L<c<27>>>,
L<c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>>>);
static_assert(std::is_same_v<apply_pack<typical::join, L<c<1>>,L<c<2>>,L<c<3>>,L<c<4>>,L<c<5>>,L<c<6>>, L<c<7>>,L<c<8>>,L<c<9>>,L<c<10>>,L<c<11>>,L<c<12>>,L<c<13>>,L<c<14>>,L<c<15>>,L<c<16>>,L<c<17>>,L<c<18>>,L<c<19>>,L<c<20>>,L<c<21>>,L<c<22>>,L<c<23>>,L<c<24>>,L<c<25>>,L<c<26>>,L<c<27>>,L<c<28>>>,
L<c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>>>);
static_assert(std::is_same_v<apply_pack<typical::join, L<c<1>>,L<c<2>>,L<c<3>>,L<c<4>>,L<c<5>>,L<c<6>>, L<c<7>>,L<c<8>>,L<c<9>>,L<c<10>>,L<c<11>>,L<c<12>>,L<c<13>>,L<c<14>>,L<c<15>>,L<c<16>>,L<c<17>>,L<c<18>>,L<c<19>>,L<c<20>>,L<c<21>>,L<c<22>>,L<c<23>>,L<c<24>>,L<c<25>>,L<c<26>>,L<c<27>>,L<c<28>>,L<c<29>>>,
L<c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>>>);
static_assert(std::is_same_v<apply_pack<typical::join, L<c<1>>,L<c<2>>,L<c<3>>,L<c<4>>,L<c<5>>,L<c<6>>, L<c<7>>,L<c<8>>,L<c<9>>,L<c<10>>,L<c<11>>,L<c<12>>,L<c<13>>,L<c<14>>,L<c<15>>,L<c<16>>,L<c<17>>,L<c<18>>,L<c<19>>,L<c<20>>,L<c<21>>,L<c<22>>,L<c<23>>,L<c<24>>,L<c<25>>,L<c<26>>,L<c<27>>,L<c<28>>,L<c<29>>,L<c<30>>>,
L<c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>>>);
static_assert(std::is_same_v<apply_pack<typical::join, L<c<1>>,L<c<2>>,L<c<3>>,L<c<4>>,L<c<5>>,L<c<6>>, L<c<7>>,L<c<8>>,L<c<9>>,L<c<10>>,L<c<11>>,L<c<12>>,L<c<13>>,L<c<14>>,L<c<15>>,L<c<16>>,L<c<17>>,L<c<18>>,L<c<19>>,L<c<20>>,L<c<21>>,L<c<22>>,L<c<23>>,L<c<24>>,L<c<25>>,L<c<26>>,L<c<27>>,L<c<28>>,L<c<29>>,L<c<30>>,L<c<31>>>,
L<c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>>>);
static_assert(std::is_same_v<apply_pack<typical::join, L<c<1>>,L<c<2>>,L<c<3>>,L<c<4>>,L<c<5>>,L<c<6>>, L<c<7>>,L<c<8>>,L<c<9>>,L<c<10>>,L<c<11>>,L<c<12>>,L<c<13>>,L<c<14>>,L<c<15>>,L<c<16>>,L<c<17>>,L<c<18>>,L<c<19>>,L<c<20>>,L<c<21>>,L<c<22>>,L<c<23>>,L<c<24>>,L<c<25>>,L<c<26>>,L<c<27>>,L<c<28>>,L<c<29>>,L<c<30>>,L<c<31>>,L<c<32>>>,
L<c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>>>);
static_assert(std::is_same_v<apply_pack<typical::join, L<c<1>>,L<c<2>>,L<c<3>>,L<c<4>>,L<c<5>>,L<c<6>>, L<c<7>>,L<c<8>>,L<c<9>>,L<c<10>>,L<c<11>>,L<c<12>>,L<c<13>>,L<c<14>>,L<c<15>>,L<c<16>>,L<c<17>>,L<c<18>>,L<c<19>>,L<c<20>>,L<c<21>>,L<c<22>>,L<c<23>>,L<c<24>>,L<c<25>>,L<c<26>>,L<c<27>>,L<c<28>>,L<c<29>>,L<c<30>>,L<c<31>>,L<c<32>>,L<c<33>>>,
L<c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>>>);
static_assert(std::is_same_v<apply_pack<typical::join, L<c<1>>,L<c<2>>,L<c<3>>,L<c<4>>,L<c<5>>,L<c<6>>, L<c<7>>,L<c<8>>,L<c<9>>,L<c<10>>,L<c<11>>,L<c<12>>,L<c<13>>,L<c<14>>,L<c<15>>,L<c<16>>,L<c<17>>,L<c<18>>,L<c<19>>,L<c<20>>,L<c<21>>,L<c<22>>,L<c<23>>,L<c<24>>,L<c<25>>,L<c<26>>,L<c<27>>,L<c<28>>,L<c<29>>,L<c<30>>,L<c<31>>,L<c<32>>,L<c<33>>,L<c<34>>>,
L<c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>>>);
static_assert(std::is_same_v<apply_pack<typical::join, L<c<1>>,L<c<2>>,L<c<3>>,L<c<4>>>, L<c<1>,c<2>,c<3>,c<4>>>);

static_assert(std::is_same_v<apply_pack<typical::join, std::tuple<int,char>, std::tuple<bool, double>>,
              typical::list<int,char,bool,double>>);
static_assert(std::is_same_v<apply_pack<typical::join, std::tuple<int>, std::tuple<char>, std::tuple<bool>, std::tuple<double>>,
              typical::list<int,char,bool,double>>);
static_assert(std::is_same_v<apply_pack<typical::join, std::tuple<int>, std::tuple<char, bool>, std::tuple<double>>,
              typical::list<int,char,bool,double>>);
static_assert(std::is_same_v<apply_pack<typical::join, std::tuple<int,char>, std::tuple<>, std::tuple<bool, double>>,
              typical::list<int,char,bool,double>>);
static_assert(std::is_same_v<apply_pack<typical::join, std::variant<int,char>, std::variant<bool,double>>,
              typical::list<int,char,bool,double>>);

static_assert(std::is_same_v<apply_pack<typical::join, L<c<1>>, L<c<2>>, L<c<3>>, L<c<4>>, L<c<5>>, L<c<6>>, L<c<7>>, L<c<8>>, L<c<9>>, L<c<10>>, L<c<11>>, L<c<12>>, L<c<13>>>,
L<c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>>>);

static_assert(std::is_same_v<typical::apply_pack_to<typical::join, typical::make<std::tuple>, std::tuple<c<1>,c<2>>, std::tuple<c<3>>, std::tuple<c<4>,c<5>,c<6>>, std::tuple<>>,
  std::tuple<c<1>,c<2>,c<3>,c<4>,c<5>,c<6>>>);
static_assert(std::is_same_v<typical::apply_pack<typical::join, std::tuple<c<1>,c<2>>, std::tuple<c<3>>, std::tuple<c<4>,c<5>,c<6>>, std::tuple<>>,
  typical::list<c<1>,c<2>,c<3>,c<4>,c<5>,c<6>>>);
