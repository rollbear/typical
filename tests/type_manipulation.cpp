#include <typical/type_manipulation.hpp>
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

