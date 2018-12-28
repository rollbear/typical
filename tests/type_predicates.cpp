#include <typical/type_predicates.hpp>
#include <variant>

template <typename>
struct wrapped;

struct wrap
{
  template <typename T>
  using result = wrapped<T>;
};

static_assert(std::is_same_v<typical::is_pointer::to<>::result<int>, typical::constant<false>>);
static_assert(std::is_same_v<typical::is_pointer::to<wrap>::result<int>, wrapped<typical::constant<false>>>);
static_assert(std::is_same_v<typical::is_pointer::to<>::result<int*>, typical::constant<true>>);

static_assert(std::is_same_v<typical::is_reference::to<>::result<int>, typical::constant<false>>);
static_assert(std::is_same_v<typical::is_reference::to<wrap>::result<int>, wrapped<typical::constant<false>>>);
static_assert(std::is_same_v<typical::is_reference::to<>::result<int&>, typical::constant<true>>);
static_assert(std::is_same_v<typical::is_reference::to<>::result<int&&>, typical::constant<true>>);

static_assert(std::is_same_v<typical::is_lvalue_reference::to<>::result<int>, typical::constant<false>>);
static_assert(std::is_same_v<typical::is_lvalue_reference::to<wrap>::result<int>, wrapped<typical::constant<false>>>);
static_assert(std::is_same_v<typical::is_lvalue_reference::to<>::result<int&>, typical::constant<true>>);
static_assert(std::is_same_v<typical::is_lvalue_reference::to<>::result<int&&>, typical::constant<false>>);

static_assert(std::is_same_v<typical::is_rvalue_reference::to<>::result<int>, typical::constant<false>>);
static_assert(std::is_same_v<typical::is_rvalue_reference::to<wrap>::result<int>, wrapped<typical::constant<false>>>);
static_assert(std::is_same_v<typical::is_rvalue_reference::to<>::result<int&>, typical::constant<false>>);
static_assert(std::is_same_v<typical::is_rvalue_reference::to<>::result<int&&>, typical::constant<true>>);

static_assert(std::is_same_v<typical::is_const::to<>::result<int>, typical::constant<false>>);
static_assert(std::is_same_v<typical::is_const::to<wrap>::result<int>, wrapped<typical::constant<false>>>);
static_assert(std::is_same_v<typical::is_const::to<>::result<int const>, typical::constant<true>>);
static_assert(std::is_same_v<typical::is_const::to<>::result<int const*>, typical::constant<false>>);
static_assert(std::is_same_v<typical::is_const::to<>::result<int const&>, typical::constant<false>>);
static_assert(std::is_same_v<typical::is_const::to<>::result<int const volatile>, typical::constant<true>>);

static_assert(std::is_same_v<typical::is_volatile::to<>::result<int>, typical::constant<false>>);
static_assert(std::is_same_v<typical::is_volatile::to<wrap>::result<int>, wrapped<typical::constant<false>>>);
static_assert(std::is_same_v<typical::is_volatile::to<>::result<int volatile>, typical::constant<true>>);
static_assert(std::is_same_v<typical::is_volatile::to<>::result<int volatile*>, typical::constant<false>>);
static_assert(std::is_same_v<typical::is_volatile::to<>::result<int volatile&>, typical::constant<false>>);
static_assert(std::is_same_v<typical::is_volatile::to<>::result<int const volatile>, typical::constant<true>>);

static_assert(std::is_same_v<typical::is_empty::to<>::result<std::tuple<>>, typical::constant<true>>);
static_assert(std::is_same_v<typical::is_empty::to<wrap>::result<std::tuple<>>, wrapped<typical::constant<true>>>);
static_assert(std::is_same_v<typical::is_empty::to<>::result<std::variant<>>, typical::constant<true>>);
static_assert(std::is_same_v<typical::is_empty::to<>::result<std::tuple<int>>, typical::constant<false>>);
static_assert(std::is_same_v<typical::is_empty::to<>::result<std::variant<int>>, typical::constant<false>>);

static_assert(std::is_same_v<typical::is_template<std::tuple>::to<>::result<std::tuple<int,char>>, typical::constant<true>>);
static_assert(std::is_same_v<typical::is_template<std::tuple>::to<wrap>::result<std::tuple<int,char>>, wrapped<typical::constant<true>>>);
static_assert(std::is_same_v<typical::is_template<std::variant>::to<>::result<std::tuple<int,char>>, typical::constant<false>>);

static_assert(std::is_same_v<typical::negate<typical::is_same<int>>::to<>::result<char>,
  typical::constant<true>>);
static_assert(std::is_same_v<typical::negate<typical::is_same<int>>::to<>::result<int>,
  typical::constant<false>>);
