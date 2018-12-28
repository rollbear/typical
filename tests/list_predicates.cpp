#include <typical/list_predicates.hpp>
#include <typical/application.hpp>

#include <tuple>
#include <variant>

template <auto N>
struct c {};

template <typename>
struct wrapped;

struct wrap
{
  template <typename T>
  using result = wrapped<T>;
};


using typical::apply_pack;

static_assert(std::is_same_v<typical::is_empty::to<>::result<std::tuple<>>, typical::constant<true>>);
static_assert(std::is_same_v<typical::is_empty::to<wrap>::result<std::tuple<>>, wrapped<typical::constant<true>>>);
static_assert(std::is_same_v<typical::is_empty::to<>::result<std::variant<>>, typical::constant<true>>);
static_assert(std::is_same_v<typical::is_empty::to<>::result<std::tuple<int>>, typical::constant<false>>);
static_assert(std::is_same_v<typical::is_empty::to<>::result<std::variant<int>>, typical::constant<false>>);

static_assert(std::is_same_v<apply_pack<typical::any_of<typical::is_reference>, int,int,double,char>,
              typical::constant<false>>);
static_assert(std::is_same_v<apply_pack<typical::any_of<typical::is_reference>, int,int&,double,char>,
              typical::constant<true>>);
static_assert(std::is_same_v<apply_pack<typical::any_of<typical::is_reference>, int&,int&,double&,char&>,
              typical::constant<true>>);

static_assert(std::is_same_v<apply_pack<typical::all_of<typical::is_reference>, int,int,double,char>,
              typical::constant<false>>);
static_assert(std::is_same_v<apply_pack<typical::all_of<typical::is_reference>, int,int&,double,char>,
              typical::constant<false>>);
static_assert(std::is_same_v<apply_pack<typical::all_of<typical::is_reference>, int&,int&,double&,char&>,
              typical::constant<true>>);

static_assert(std::is_same_v<apply_pack<typical::none_of<typical::is_reference>, int,int,double,char>,
              typical::constant<true>>);
static_assert(std::is_same_v<apply_pack<typical::none_of<typical::is_reference>, int,int&,double,char>,
              typical::constant<false>>);
static_assert(std::is_same_v<apply_pack<typical::none_of<typical::is_reference>, int&,int&,double&,char&>,
              typical::constant<false>>);

static_assert(std::is_same_v<apply_pack<typical::has<int>, void, int, bool>,
              typical::constant<true>>);
static_assert(std::is_same_v<apply_pack<typical::has<void>, void, int, bool>,
              typical::constant<true>>);
static_assert(std::is_same_v<apply_pack<typical::has<bool>, void, int, bool>,
              typical::constant<true>>);
static_assert(std::is_same_v<apply_pack<typical::has<char>, void, int, bool>,
              typical::constant<false>>);
static_assert(std::is_same_v<apply_pack<typical::has<char>>,
              typical::constant<false>>);

static_assert(std::is_same_v<apply_pack<typical::all_unique, c<1>,c<2>,c<3>,c<4>>,
              typical::constant<true>>);
static_assert(std::is_same_v<apply_pack<typical::all_unique, c<1>,c<2>,c<3>,c<1>>,
              typical::constant<false>>);
static_assert(std::is_same_v<apply_pack<typical::all_unique, c<1>,c<2>,c<1>,c<3>>,
              typical::constant<false>>);
static_assert(std::is_same_v<apply_pack<typical::all_unique, c<1>,c<2>,c<3>,c<1>>,
              typical::constant<false>>);
static_assert(std::is_same_v<apply_pack<typical::all_unique, c<1>,c<2>,c<3>,c<3>>,
              typical::constant<false>>);
