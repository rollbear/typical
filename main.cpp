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


template <typename T>
void ignore();
struct is_even {
  template <typename T>
  using f = typical::constant<T::value % 2 == 0>;
};

int main()
{
}
