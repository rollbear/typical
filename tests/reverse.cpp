#include <typical/algorithms/reverse.hpp>

template <auto>
class c;

using typical::apply_pack;
using typical::apply_pack_to;

static_assert(std::is_same_v<apply_pack<typical::reverse, c<1>>,
typical::list<c<1>>>);
static_assert(std::is_same_v<apply_pack<typical::reverse, c<1>,c<2>>,
              typical::list<c<2>,c<1>>>);
static_assert(std::is_same_v<apply_pack<typical::reverse, c<1>,c<2>,c<3>>,
              typical::list<c<3>,c<2>,c<1>>>);
static_assert(std::is_same_v<apply_pack<typical::reverse, c<1>,c<2>,c<3>,c<4>>,
              typical::list<c<4>,c<3>,c<2>,c<1>>>);
static_assert(std::is_same_v<apply_pack<typical::reverse, c<1>,c<2>,c<3>,c<4>,c<5>>,
              typical::list<c<5>,c<4>,c<3>,c<2>,c<1>>>);
static_assert(std::is_same_v<apply_pack<typical::reverse, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>>,
              typical::list<c<6>,c<5>,c<4>,c<3>,c<2>,c<1>>>);
static_assert(std::is_same_v<apply_pack<typical::reverse, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>>,
              typical::list<c<7>,c<6>,c<5>,c<4>,c<3>,c<2>,c<1>>>);
static_assert(std::is_same_v<apply_pack<typical::reverse, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>>,
              typical::list<c<8>,c<7>,c<6>,c<5>,c<4>,c<3>,c<2>,c<1>>>);
static_assert(std::is_same_v<apply_pack<typical::reverse, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>>,
              typical::list<c<9>,c<8>,c<7>,c<6>,c<5>,c<4>,c<3>,c<2>,c<1>>>);
static_assert(std::is_same_v<apply_pack<typical::reverse, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>>,
              typical::list<c<10>,c<9>,c<8>,c<7>,c<6>,c<5>,c<4>,c<3>,c<2>,c<1>>>);
static_assert(std::is_same_v<apply_pack<typical::reverse, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>>,
              typical::list<c<11>,c<10>,c<9>,c<8>,c<7>,c<6>,c<5>,c<4>,c<3>,c<2>,c<1>>>);
static_assert(std::is_same_v<apply_pack<typical::reverse, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>>,
              typical::list<c<12>,c<11>,c<10>,c<9>,c<8>,c<7>,c<6>,c<5>,c<4>,c<3>,c<2>,c<1>>>);
static_assert(std::is_same_v<apply_pack<typical::reverse, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>>,
              typical::list<c<13>,c<12>,c<11>,c<10>,c<9>,c<8>,c<7>,c<6>,c<5>,c<4>,c<3>,c<2>,c<1>>>);
static_assert(std::is_same_v<apply_pack<typical::reverse, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>>,
              typical::list<c<14>,c<13>,c<12>,c<11>,c<10>,c<9>,c<8>,c<7>,c<6>,c<5>,c<4>,c<3>,c<2>,c<1>>>);
static_assert(std::is_same_v<apply_pack<typical::reverse, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>>,
              typical::list<c<15>,c<14>,c<13>,c<12>,c<11>,c<10>,c<9>,c<8>,c<7>,c<6>,c<5>,c<4>,c<3>,c<2>,c<1>>>);
static_assert(std::is_same_v<apply_pack<typical::reverse, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>>,
              typical::list<c<16>,c<15>,c<14>,c<13>,c<12>,c<11>,c<10>,c<9>,c<8>,c<7>,c<6>,c<5>,c<4>,c<3>,c<2>,c<1>>>);
static_assert(std::is_same_v<apply_pack<typical::reverse, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>>,
              typical::list<c<17>,c<16>,c<15>,c<14>,c<13>,c<12>,c<11>,c<10>,c<9>,c<8>,c<7>,c<6>,c<5>,c<4>,c<3>,c<2>,c<1>>>);
static_assert(std::is_same_v<apply_pack<typical::reverse, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>>,
              typical::list<c<18>,c<17>,c<16>,c<15>,c<14>,c<13>,c<12>,c<11>,c<10>,c<9>,c<8>,c<7>,c<6>,c<5>,c<4>,c<3>,c<2>,c<1>>>);
static_assert(std::is_same_v<apply_pack<typical::reverse, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>>,
              typical::list<c<19>,c<18>,c<17>,c<16>,c<15>,c<14>,c<13>,c<12>,c<11>,c<10>,c<9>,c<8>,c<7>,c<6>,c<5>,c<4>,c<3>,c<2>,c<1>>>);
static_assert(std::is_same_v<apply_pack<typical::reverse, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>>,
              typical::list<c<20>,c<19>,c<18>,c<17>,c<16>,c<15>,c<14>,c<13>,c<12>,c<11>,c<10>,c<9>,c<8>,c<7>,c<6>,c<5>,c<4>,c<3>,c<2>,c<1>>>);
static_assert(std::is_same_v<apply_pack<typical::reverse, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>>,
              typical::list<c<21>,c<20>,c<19>,c<18>,c<17>,c<16>,c<15>,c<14>,c<13>,c<12>,c<11>,c<10>,c<9>,c<8>,c<7>,c<6>,c<5>,c<4>,c<3>,c<2>,c<1>>>);

static_assert(std::is_same_v<apply_pack_to<typical::reverse, typical::make<std::tuple>, int, char, double>,
  std::tuple<double, char, int>>);
