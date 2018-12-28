#include <typical.hpp>
#include <tuple>
#include <variant>

template <auto N>
struct c {};

using typical::apply_pack;
using typical::apply_one;


template <typename...>
struct S;//{S() = delete;};


static_assert(std::is_same_v<apply_pack<typical::is_empty, typical::list<>>,
  typical::constant<true>>);
static_assert(std::is_same_v<apply_pack<typical::is_empty, std::tuple<>>,
  typical::constant<true>>);
static_assert(std::is_same_v<apply_pack<typical::is_empty, typical::list<int>>,
  typical::constant<false>>);
static_assert(std::is_same_v<apply_pack<typical::is_empty, std::tuple<bool>>,
  typical::constant<false>>);


static_assert(std::is_same_v<apply_pack<typical::compose<typical::add_const, typical::add_pointer, typical::add_volatile>, int>,
              int volatile * const>);

static_assert(std::is_same_v<apply_pack<typical::remove_cv, const int volatile>, int>);
static_assert(std::is_same_v<apply_pack<typical::remove_cv, int>, int>);
static_assert(std::is_same_v<apply_pack<typical::remove_cv_ref, int const volatile&>, int>);
static_assert(std::is_same_v<apply_pack<typical::remove_cv_ref, int const volatile&&>, int>);


//static_assert(std::is_same_v<apply_pack<typical::metamorph<std::variant>, std::tuple<int,char,double>>,
//  std::variant<int,char,double>>);
//static_assert(std::is_same_v<apply_pack<typical::metamorph<std::variant>, std::tuple<>>,
//  std::variant<>>);


template <typename ... Ts>
using L = typical::list<Ts...>;

//L<1>,L<2>,L<3>,L<4>,L<5>,L<6>,L<7>,L<8>,L<9>,L<10>,L<11>,L<12>,L<13>,L<14>,L<15>,L<16>,L<17>,L<18>,L<19>,L<20>,L<21>,L<22>,L<23>,L<24>,L<25>,L<26>,L<27>,L<28>,L<29>,L<30>,L<31>,L<32>,L<33>
//5, L<1>,L<2>,L<3>,L<4>,L<5>,L<6>,L<7>,L<8>,L<9>,L<10>,L<11>,L<12>,L<13>,L<14>,L<15>,L<16>,L<17>,L<18>,L<19>,L<20>,L<21>,L<22>,L<23>,L<24>,L<25>,L<26>,L<27>,L<28>,L<29>,L<30>,L<31>,L<32>,L<33>
// L<1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16>,L<17>,L<18>,L<19>,L<20>,L<21>,L<22>,L<23>,L<24>,L<25>,L<26>,L<27>,L<28>,L<29>,L<30>,L<31>,L<32>,L<33>
//4 L<1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16>,L<17>,L<18>,L<19>,L<20>,L<21>,L<22>,L<23>,L<24>,L<25>,L<26>,L<27>,L<28>,L<29>,L<30>,L<31>,L<32>,L<33>
// L<1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31>, L<32>,L<33>
// 1 L<1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31>, L<32>,L<33>
// L<1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32>,L<33>
// 1 L<1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32>,L<33>

struct make_pair
{
  using continuation = typical::identity;
  template <typename C = continuation>
  struct to {
    template<typename T, typename U>
    using result = typename C::template result<std::pair<T, U>>;
  };
};


static_assert(std::is_same_v<apply_pack<typical::zip<::make_pair>, std::tuple<int,char>, std::variant<bool,double>>,
  typical::list<std::pair<int,bool>, std::pair<char,double>>>);

static_assert(std::is_same_v<apply_pack<typical::partition<typical::is_pointer>, int,void*,int*, double, char*>,
  typical::list<typical::list<void*,int*,char*>,typical::list<int,double>>>);


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

static_assert(std::is_same_v<apply_pack<typical::flatten,
  typical::list<c<1>,c<2>,typical::list<c<3>, c<4>, typical::list<c<5>, c<6>>>,std::tuple<c<7>, c<8>, typical::list<c<9>,c<10>>>,typical::list<c<11>,typical::list<c<12>,typical::list<c<13>>>>>>,
  typical::list<c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,std::tuple<c<7>,c<8>,typical::list<c<9>,c<10>>>,c<11>,c<12>,c<13>>>);




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



template <typename T>
void ignore();
struct is_even {
  template <typename T>
  using f = typical::constant<T::value % 2 == 0>;
};

int main()
{
}
