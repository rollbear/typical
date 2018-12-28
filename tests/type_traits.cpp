#include <typical/type_traits.hpp>
#include <variant>
template <typename>
struct wrapped;

struct wrap
{
  template <typename T>
  using result = wrapped<T>;
};

static_assert(std::is_same_v<typical::add_pointer::to<>::result<int>, int*>);
static_assert(std::is_same_v<typical::add_pointer::to<wrap>::result<int>, wrapped<int*>>);

static_assert(std::is_same_v<typical::add_lvalue_reference::to<>::result<int>, int&>);
static_assert(std::is_same_v<typical::add_lvalue_reference::to<wrap>::result<int>, wrapped<int&>>);

static_assert(std::is_same_v<typical::add_rvalue_reference::to<>::result<int>, int&&>);
static_assert(std::is_same_v<typical::add_rvalue_reference::to<wrap>::result<int>, wrapped<int&&>>);

static_assert(std::is_same_v<typical::add_const::to<>::result<int>, int const>);
static_assert(std::is_same_v<typical::add_const::to<wrap>::result<int>, wrapped<int const>>);

static_assert(std::is_same_v<typical::add_volatile::to<>::result<int>, int volatile>);
static_assert(std::is_same_v<typical::add_volatile::to<wrap>::result<int>, wrapped<int volatile>>);

static_assert(std::is_same_v<typical::remove_cv::to<>::result<int>, int>);
static_assert(std::is_same_v<typical::remove_cv::to<wrap>::result<int>, wrapped<int>>);
static_assert(std::is_same_v<typical::remove_cv::to<>::result<int const>, int>);
static_assert(std::is_same_v<typical::remove_cv::to<>::result<int volatile>, int>);
static_assert(std::is_same_v<typical::remove_cv::to<>::result<int const volatile>, int>);
static_assert(std::is_same_v<typical::remove_cv::to<>::result<int const volatile&>, int const volatile&>);

static_assert(std::is_same_v<typical::remove_cv_ref::to<>::result<int>, int>);
static_assert(std::is_same_v<typical::remove_cv_ref::to<wrap>::result<int>, wrapped<int>>);
static_assert(std::is_same_v<typical::remove_cv_ref::to<>::result<int const>, int>);
static_assert(std::is_same_v<typical::remove_cv_ref::to<>::result<int const&>, int>);
static_assert(std::is_same_v<typical::remove_cv_ref::to<>::result<int const&&>, int>);
static_assert(std::is_same_v<typical::remove_cv_ref::to<>::result<int volatile>, int>);
static_assert(std::is_same_v<typical::remove_cv_ref::to<>::result<int volatile&>, int>);
static_assert(std::is_same_v<typical::remove_cv_ref::to<>::result<int volatile&&>, int>);
static_assert(std::is_same_v<typical::remove_cv_ref::to<>::result<int const volatile>, int>);
static_assert(std::is_same_v<typical::remove_cv_ref::to<>::result<int const volatile&>, int>);
static_assert(std::is_same_v<typical::remove_cv_ref::to<>::result<int const volatile&&>, int>);

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
