#include <typical.hpp>
#include <tuple>
#include <variant>

template <auto N>
struct c {};

static_assert(typical::constant_v<3> == 3);
static_assert(std::is_same_v<decltype(typical::constant_v<' '>), const char>);
static_assert(std::is_same_v<decltype(typical::constant<5>::value), const int>);

using typical::apply;


static_assert(std::is_same_v<apply<typical::bind_front<std::tuple, int, char>, bool, double>,
std::tuple<int,char,bool,double>>);
static_assert(std::is_same_v<apply<typical::add_pointer<>, int>, int*>);
static_assert(std::is_same_v<apply<typical::add_lvalue_reference<>, int const>, int const&>);
static_assert(std::is_same_v<apply<typical::add_rvalue_reference<>, int volatile>, int volatile&&>);
static_assert(std::is_same_v<apply<typical::add_const<>, int>, int const>);
static_assert(std::is_same_v<apply<typical::add_volatile<>, int>, int volatile>);
static_assert(std::is_same_v<apply<typical::remove_reference<>, int&>, int>);
static_assert(std::is_same_v<apply<typical::remove_reference<>, int&&>, int>);
static_assert(std::is_same_v<apply<typical::remove_pointer<>, int const * const>, int const>);
static_assert(std::is_same_v<apply<typical::remove_const<>, int const * const>, int const*>);
static_assert(std::is_same_v<apply<typical::remove_const<>, int *>, int *>);
static_assert(std::is_same_v<apply<typical::remove_volatile<>, int const volatile>, int const>);
static_assert(apply<typical::is_same<int>, int>::value);
static_assert(!apply<typical::is_same<int>, char>::value);
static_assert(apply<typical::is_pointer<>, int*>::value);
static_assert(!apply<typical::is_pointer<>, int>::value);
static_assert(apply<typical::is_reference<>, int&&>::value);
static_assert(apply<typical::is_reference<>, int&>::value);
static_assert(!apply<typical::is_reference<>, int>::value);
static_assert(!apply<typical::is_lvalue_reference<>, int&&>::value);
static_assert(apply<typical::is_lvalue_reference<>, int&>::value);
static_assert(!apply<typical::is_lvalue_reference<>, int>::value);
static_assert(apply<typical::is_rvalue_reference<>, int&&>::value);
static_assert(!apply<typical::is_rvalue_reference<>, int&>::value);
static_assert(!apply<typical::is_rvalue_reference<>, int>::value);
static_assert(apply<typical::is_const<>, int const>::value);
static_assert(!apply<typical::is_const<>, int>::value);
static_assert(apply<typical::is_volatile<>, int volatile>::value);
static_assert(!apply<typical::is_volatile<>, int>::value);

static_assert(apply<typical::is_template<std::tuple>, std::tuple<int,char>>::value);
static_assert(!apply<typical::is_template<std::variant>, std::tuple<int,char>>::value);

static_assert(apply<typical::negate<typical::is_same<int>>, char>::value);
static_assert(!apply<typical::negate<typical::is_same<int>>, int>::value);
template <typename...>
struct S;
//S<apply<typical::compose<typical::add_const, typical::add_pointer, typical::add_volatile>::type<typical::identity>, int>> s;

static_assert(std::is_same_v<apply<typical::compose<typical::add_const, typical::add_pointer, typical::add_volatile>::type<typical::identity>, int>,
              int volatile * const>);

static_assert(std::is_same_v<apply<typical::remove_cv<>, const int volatile>, int>);
static_assert(std::is_same_v<apply<typical::remove_cv<>, int>, int>);
//static_assert(std::is_same_v<apply<typical::remove_cv_ref<>, int const volatile&>, int>);
//static_assert(std::is_same_v<apply<typical::remove_cv_ref<>, int const volatile&&>, int>);

static_assert(std::is_same_v<apply<typical::transform<typical::add_pointer<>>, int,char,double>,
typical::type_list<int*,char*,double*>>);
static_assert(std::is_same_v<apply<typical::transform<typical::add_pointer<>>>, typical::type_list<>>);
static_assert(std::is_same_v<apply<typical::unwrap<typical::transform<typical::add_pointer<>>>, std::tuple<int,char,double>>, typical::type_list<int*,char*,double*>>);

static_assert(std::is_same_v<apply<typical::metamorph<std::variant>, std::tuple<int,char,double>>,
  std::variant<int,char,double>>);
static_assert(std::is_same_v<apply<typical::metamorph<std::variant>, std::tuple<>>,
  std::variant<>>);

static_assert(std::is_same_v<apply<typical::concat<>, std::tuple<int,char>, std::tuple<bool, double>>,
  typical::type_list<int,char,bool,double>>);
static_assert(std::is_same_v<apply<typical::concat<>, std::tuple<int>, std::tuple<char>, std::tuple<bool>, std::tuple<double>>,
  typical::type_list<int,char,bool,double>>);
static_assert(std::is_same_v<apply<typical::concat<>, std::tuple<int>, std::tuple<char, bool>, std::tuple<double>>,
  typical::type_list<int,char,bool,double>>);
static_assert(std::is_same_v<apply<typical::concat<>, std::tuple<int,char>, std::tuple<>, std::tuple<bool, double>>,
  typical::type_list<int,char,bool,double>>);
static_assert(std::is_same_v<apply<typical::concat<>, std::variant<int,char>, std::variant<bool,double>>,
typical::type_list<int,char,bool,double>>);

template <typename ... Ts>
using L = typical::type_list<Ts...>;

static_assert(std::is_same_v<apply<typical::concat<>, L<c<1>>, L<c<2>>, L<c<3>>, L<c<4>>, L<c<5>>, L<c<6>>, L<c<7>>, L<c<8>>, L<c<9>>, L<c<10>>, L<c<11>>, L<c<12>>, L<c<13>>>,
  L<c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>>>);

static_assert(apply<typical::size, std::variant<int,char,bool>>::value == 3);

struct make_pair
{
  template <typename T, typename U>
  using f = std::pair<T,U>;
};


static_assert(std::is_same_v<apply<typical::zip<::make_pair>, std::tuple<int,char>, std::variant<bool,double>>,
  typical::type_list<std::pair<int,bool>, std::pair<char,double>>>);

static_assert(std::is_same_v<apply<typical::filter<typical::is_pointer<>>, std::tuple<int, void*, int*, double, char*>>,
  typical::type_list<void*, int*, char*>>);

static_assert(std::is_same_v<apply<typical::partition<typical::is_pointer<>>, int,void*,int*, double, char*>,
  typical::type_list<typical::type_list<void*,int*,char*>,typical::type_list<int,double>>>);



static_assert(std::is_same_v<apply<typical::count_if<typical::is_pointer<>>,int,int*,void*,double>,
                typical::constant<2UL>>);
static_assert(std::is_same_v<apply<typical::count_if<typical::is_reference<>>,int,int*,void*,double>,
  typical::constant<0UL>>);
static_assert(std::is_same_v<apply<typical::count_if<typical::is_same<int>>,int,int*,void*,double>,
  typical::constant<1UL>>);

static_assert(std::is_same_v<apply<typical::any_of<typical::is_reference<>>, std::tuple<int,int,double,char>>,
  typical::constant<false>>);
static_assert(std::is_same_v<apply<typical::any_of<typical::is_reference<>>, std::tuple<int,int&,double,char>>,
  typical::constant<true>>);
static_assert(std::is_same_v<apply<typical::any_of<typical::is_reference<>>, std::tuple<int&,int&,double&,char&>>,
  typical::constant<true>>);

static_assert(std::is_same_v<apply<typical::all_of<typical::is_reference<>>, std::tuple<int,int,double,char>>,
  typical::constant<false>>);
static_assert(std::is_same_v<apply<typical::all_of<typical::is_reference<>>, std::tuple<int,int&,double,char>>,
  typical::constant<false>>);
static_assert(std::is_same_v<apply<typical::all_of<typical::is_reference<>>, std::tuple<int&,int&,double&,char&>>,
  typical::constant<true>>);

static_assert(std::is_same_v<apply<typical::none_of<typical::is_reference<>>, std::tuple<int,int,double,char>>,
  typical::constant<true>>);
static_assert(std::is_same_v<apply<typical::none_of<typical::is_reference<>>, std::tuple<int,int&,double,char>>,
  typical::constant<false>>);
static_assert(std::is_same_v<apply<typical::none_of<typical::is_reference<>>, std::tuple<int&,int&,double&,char&>>,
  typical::constant<false>>);

static_assert(std::is_same_v<apply<typical::reverse<>, c<1>>,
  typical::type_list<c<1>>>);
static_assert(std::is_same_v<apply<typical::reverse<>, c<1>,c<2>>,
  typical::type_list<c<2>,c<1>>>);
static_assert(std::is_same_v<apply<typical::reverse<>, c<1>,c<2>,c<3>>,
  typical::type_list<c<3>,c<2>,c<1>>>);
static_assert(std::is_same_v<apply<typical::reverse<>, c<1>,c<2>,c<3>,c<4>>,
  typical::type_list<c<4>,c<3>,c<2>,c<1>>>);
static_assert(std::is_same_v<apply<typical::reverse<>, c<1>,c<2>,c<3>,c<4>,c<5>>,
  typical::type_list<c<5>,c<4>,c<3>,c<2>,c<1>>>);
static_assert(std::is_same_v<apply<typical::reverse<>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>>,
  typical::type_list<c<6>,c<5>,c<4>,c<3>,c<2>,c<1>>>);
static_assert(std::is_same_v<apply<typical::reverse<>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>>,
  typical::type_list<c<7>,c<6>,c<5>,c<4>,c<3>,c<2>,c<1>>>);
static_assert(std::is_same_v<apply<typical::reverse<>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>>,
  typical::type_list<c<8>,c<7>,c<6>,c<5>,c<4>,c<3>,c<2>,c<1>>>);
static_assert(std::is_same_v<apply<typical::reverse<>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>>,
  typical::type_list<c<9>,c<8>,c<7>,c<6>,c<5>,c<4>,c<3>,c<2>,c<1>>>);
static_assert(std::is_same_v<apply<typical::reverse<>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>>,
  typical::type_list<c<10>,c<9>,c<8>,c<7>,c<6>,c<5>,c<4>,c<3>,c<2>,c<1>>>);
static_assert(std::is_same_v<apply<typical::reverse<>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>>,
  typical::type_list<c<11>,c<10>,c<9>,c<8>,c<7>,c<6>,c<5>,c<4>,c<3>,c<2>,c<1>>>);
static_assert(std::is_same_v<apply<typical::reverse<>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>>,
  typical::type_list<c<12>,c<11>,c<10>,c<9>,c<8>,c<7>,c<6>,c<5>,c<4>,c<3>,c<2>,c<1>>>);
static_assert(std::is_same_v<apply<typical::reverse<>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>>,
  typical::type_list<c<13>,c<12>,c<11>,c<10>,c<9>,c<8>,c<7>,c<6>,c<5>,c<4>,c<3>,c<2>,c<1>>>);
static_assert(std::is_same_v<apply<typical::reverse<>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>>,
  typical::type_list<c<14>,c<13>,c<12>,c<11>,c<10>,c<9>,c<8>,c<7>,c<6>,c<5>,c<4>,c<3>,c<2>,c<1>>>);
static_assert(std::is_same_v<apply<typical::reverse<>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>>,
  typical::type_list<c<15>,c<14>,c<13>,c<12>,c<11>,c<10>,c<9>,c<8>,c<7>,c<6>,c<5>,c<4>,c<3>,c<2>,c<1>>>);
static_assert(std::is_same_v<apply<typical::reverse<>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>>,
  typical::type_list<c<16>,c<15>,c<14>,c<13>,c<12>,c<11>,c<10>,c<9>,c<8>,c<7>,c<6>,c<5>,c<4>,c<3>,c<2>,c<1>>>);
static_assert(std::is_same_v<apply<typical::reverse<>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>>,
  typical::type_list<c<17>,c<16>,c<15>,c<14>,c<13>,c<12>,c<11>,c<10>,c<9>,c<8>,c<7>,c<6>,c<5>,c<4>,c<3>,c<2>,c<1>>>);
static_assert(std::is_same_v<apply<typical::reverse<>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>>,
  typical::type_list<c<18>,c<17>,c<16>,c<15>,c<14>,c<13>,c<12>,c<11>,c<10>,c<9>,c<8>,c<7>,c<6>,c<5>,c<4>,c<3>,c<2>,c<1>>>);
static_assert(std::is_same_v<apply<typical::reverse<>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>>,
  typical::type_list<c<19>,c<18>,c<17>,c<16>,c<15>,c<14>,c<13>,c<12>,c<11>,c<10>,c<9>,c<8>,c<7>,c<6>,c<5>,c<4>,c<3>,c<2>,c<1>>>);
static_assert(std::is_same_v<apply<typical::reverse<>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>>,
  typical::type_list<c<20>,c<19>,c<18>,c<17>,c<16>,c<15>,c<14>,c<13>,c<12>,c<11>,c<10>,c<9>,c<8>,c<7>,c<6>,c<5>,c<4>,c<3>,c<2>,c<1>>>);
static_assert(std::is_same_v<apply<typical::reverse<>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>>,
  typical::type_list<c<21>,c<20>,c<19>,c<18>,c<17>,c<16>,c<15>,c<14>,c<13>,c<12>,c<11>,c<10>,c<9>,c<8>,c<7>,c<6>,c<5>,c<4>,c<3>,c<2>,c<1>>>);


static_assert(std::is_same_v<apply<typical::flatten<>,
  typical::type_list<c<1>,c<2>,typical::type_list<c<3>, c<4>, typical::type_list<c<5>, c<6>>>,std::tuple<c<7>, c<8>, typical::type_list<c<9>,c<10>>>,typical::type_list<c<11>,typical::type_list<c<12>,typical::type_list<c<13>>>>>>,
  typical::type_list<c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,std::tuple<c<7>,c<8>,typical::type_list<c<9>,c<10>>>,c<11>,c<12>,c<13>>>);

static_assert(std::is_same_v<apply<typical::drop_first<typical::constant<1>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  typical::type_list<c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>>);
static_assert(std::is_same_v<apply<typical::drop_first<typical::constant<2>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  typical::type_list<c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>>);
static_assert(std::is_same_v<apply<typical::drop_first<typical::constant<3>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  typical::type_list<c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>>);
static_assert(std::is_same_v<apply<typical::drop_first<typical::constant<4>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  typical::type_list<c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>>);
static_assert(std::is_same_v<apply<typical::drop_first<typical::constant<5>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  typical::type_list<c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>>);
static_assert(std::is_same_v<apply<typical::drop_first<typical::constant<6>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  typical::type_list<c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>>);
static_assert(std::is_same_v<apply<typical::drop_first<typical::constant<7>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  typical::type_list<c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>>);
static_assert(std::is_same_v<apply<typical::drop_first<typical::constant<8>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  typical::type_list<c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>>);
static_assert(std::is_same_v<apply<typical::drop_first<typical::constant<9>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  typical::type_list<c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>>);
static_assert(std::is_same_v<apply<typical::drop_first<typical::constant<10>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  typical::type_list<c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>>);
static_assert(std::is_same_v<apply<typical::drop_first<typical::constant<11>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  typical::type_list<c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>>);
static_assert(std::is_same_v<apply<typical::drop_first<typical::constant<12>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  typical::type_list<c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>>);
static_assert(std::is_same_v<apply<typical::drop_first<typical::constant<13>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  typical::type_list<c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>>);
static_assert(std::is_same_v<apply<typical::drop_first<typical::constant<14>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  typical::type_list<c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>>);
static_assert(std::is_same_v<apply<typical::drop_first<typical::constant<15>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  typical::type_list<c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>>);
static_assert(std::is_same_v<apply<typical::drop_first<typical::constant<16>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  typical::type_list<c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>>);
static_assert(std::is_same_v<apply<typical::drop_first<typical::constant<17>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  typical::type_list<c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>>);
static_assert(std::is_same_v<apply<typical::drop_first<typical::constant<18>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  typical::type_list<c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>>);
static_assert(std::is_same_v<apply<typical::drop_first<typical::constant<19>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  typical::type_list<c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>>);

static_assert(std::is_same_v<apply<typical::drop_first<typical::constant<20>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  typical::type_list<c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>>);
static_assert(std::is_same_v<apply<typical::drop_first<typical::constant<21>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  typical::type_list<c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>>);
static_assert(std::is_same_v<apply<typical::drop_first<typical::constant<22>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  typical::type_list<c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>>);
static_assert(std::is_same_v<apply<typical::drop_first<typical::constant<23>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  typical::type_list<c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>>);
static_assert(std::is_same_v<apply<typical::drop_first<typical::constant<24>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  typical::type_list<c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>>);
static_assert(std::is_same_v<apply<typical::drop_first<typical::constant<25>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  typical::type_list<c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>>);
static_assert(std::is_same_v<apply<typical::drop_first<typical::constant<26>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  typical::type_list<c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>>);
static_assert(std::is_same_v<apply<typical::drop_first<typical::constant<27>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  typical::type_list<c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>>);
static_assert(std::is_same_v<apply<typical::drop_first<typical::constant<28>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  typical::type_list<c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>>);
static_assert(std::is_same_v<apply<typical::drop_first<typical::constant<29>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  typical::type_list<c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>>);
static_assert(std::is_same_v<apply<typical::drop_first<typical::constant<30>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  typical::type_list<c<31>,c<32>,c<33>,c<34>,c<35>>>);
static_assert(std::is_same_v<apply<typical::drop_first<typical::constant<31>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  typical::type_list<c<32>,c<33>,c<34>,c<35>>>);
static_assert(std::is_same_v<apply<typical::drop_first<typical::constant<32>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  typical::type_list<c<33>,c<34>,c<35>>>);
static_assert(std::is_same_v<apply<typical::drop_first<typical::constant<33>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  typical::type_list<c<34>,c<35>>>);
static_assert(std::is_same_v<apply<typical::drop_first<typical::constant<34>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  typical::type_list<c<35>>>);
static_assert(std::is_same_v<apply<typical::drop_first<typical::constant<35>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  typical::type_list<>>);

static_assert(std::is_same_v<apply<typical::nth_type<typical::constant<0>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  c<1>>);
static_assert(std::is_same_v<apply<typical::nth_type<typical::constant<1>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  c<2>>);
static_assert(std::is_same_v<apply<typical::nth_type<typical::constant<2>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  c<3>>);
static_assert(std::is_same_v<apply<typical::nth_type<typical::constant<3>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  c<4>>);
static_assert(std::is_same_v<apply<typical::nth_type<typical::constant<4>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  c<5>>);
static_assert(std::is_same_v<apply<typical::nth_type<typical::constant<5>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  c<6>>);
static_assert(std::is_same_v<apply<typical::nth_type<typical::constant<6>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  c<7>>);
static_assert(std::is_same_v<apply<typical::nth_type<typical::constant<7>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  c<8>>);
static_assert(std::is_same_v<apply<typical::nth_type<typical::constant<8>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  c<9>>);
static_assert(std::is_same_v<apply<typical::nth_type<typical::constant<9>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  c<10>>);
static_assert(std::is_same_v<apply<typical::nth_type<typical::constant<10>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  c<11>>);
static_assert(std::is_same_v<apply<typical::nth_type<typical::constant<11>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  c<12>>);
static_assert(std::is_same_v<apply<typical::nth_type<typical::constant<12>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  c<13>>);
static_assert(std::is_same_v<apply<typical::nth_type<typical::constant<13>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  c<14>>);
static_assert(std::is_same_v<apply<typical::nth_type<typical::constant<14>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  c<15>>);
static_assert(std::is_same_v<apply<typical::nth_type<typical::constant<15>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  c<16>>);
static_assert(std::is_same_v<apply<typical::nth_type<typical::constant<16>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  c<17>>);
static_assert(std::is_same_v<apply<typical::nth_type<typical::constant<17>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  c<18>>);
static_assert(std::is_same_v<apply<typical::nth_type<typical::constant<18>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  c<19>>);
static_assert(std::is_same_v<apply<typical::nth_type<typical::constant<19>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  c<20>>);
static_assert(std::is_same_v<apply<typical::nth_type<typical::constant<20>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  c<21>>);
static_assert(std::is_same_v<apply<typical::nth_type<typical::constant<21>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  c<22>>);
static_assert(std::is_same_v<apply<typical::nth_type<typical::constant<22>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  c<23>>);
static_assert(std::is_same_v<apply<typical::nth_type<typical::constant<23>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  c<24>>);
static_assert(std::is_same_v<apply<typical::nth_type<typical::constant<24>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  c<25>>);
static_assert(std::is_same_v<apply<typical::nth_type<typical::constant<25>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  c<26>>);
static_assert(std::is_same_v<apply<typical::nth_type<typical::constant<26>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  c<27>>);
static_assert(std::is_same_v<apply<typical::nth_type<typical::constant<27>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  c<28>>);
static_assert(std::is_same_v<apply<typical::nth_type<typical::constant<28>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  c<29>>);
static_assert(std::is_same_v<apply<typical::nth_type<typical::constant<29>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  c<30>>);
static_assert(std::is_same_v<apply<typical::nth_type<typical::constant<30>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  c<31>>);
static_assert(std::is_same_v<apply<typical::nth_type<typical::constant<31>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  c<32>>);
static_assert(std::is_same_v<apply<typical::nth_type<typical::constant<32>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  c<33>>);
static_assert(std::is_same_v<apply<typical::nth_type<typical::constant<33>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  c<34>>);
static_assert(std::is_same_v<apply<typical::nth_type<typical::constant<34>>, c<1>,c<2>,c<3>,c<4>,c<5>,c<6>,c<7>,c<8>,c<9>,c<10>,c<11>,c<12>,c<13>,c<14>,c<15>,c<16>,c<17>,c<18>,c<19>,c<20>,c<21>,c<22>,c<23>,c<24>,c<25>,c<26>,c<27>,c<28>,c<29>,c<30>,c<31>,c<32>,c<33>,c<34>,c<35>>,
  c<35>>);

template <typename T>
void ignore();

int main()
{
}
