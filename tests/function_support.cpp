#include <typical/function_support.hpp>

template <typename>
struct is_int
{
  static constexpr bool value = false;
};

template <>
struct is_int<int>
{
  static constexpr bool value = true;
};

template <typename T>
struct add_const
{
  using type = const T;
};

struct value_to_integral_constant
{
  template <typename T>
  using result = std::integral_constant<typename T::type, T::value>;
};

template <typename T>
struct wrapped {};

struct wrap
{
  template <typename T>
  using result = wrapped<T>;
};
static_assert(std::is_same_v<typical::from_value<is_int>::to<>::result<char>,
  typical::constant<false>>);
static_assert(std::is_same_v<typical::from_value<is_int>::to<>::result<int>,
  typical::constant<true>>);
static_assert(std::is_same_v<typical::from_value<is_int>::to<value_to_integral_constant>::result<char>,
  std::bool_constant<false>>);
static_assert(std::is_same_v<typical::from_value<is_int>::to<value_to_integral_constant>::result<int>,
  std::bool_constant<true>>);

static_assert(std::is_same_v<typical::from_type<add_const>::to<>::result<char>,
  const char>);
static_assert(std::is_same_v<typical::from_type<add_const>::to<wrap>::result<char>,
  wrapped<const char>>);