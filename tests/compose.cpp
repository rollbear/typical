#include <typical/compose.hpp>

struct add_const
{
  using continuation = typical::identity;
  template <typename C = continuation>
  struct to
  {
    template <typename T>
    struct inner {
      using type = typical::apply_one<C, const T>;
    };
    template <typename ...T>
    using result = typename inner<T...>::type;
  };
};

struct add_pointer
{
  using continuation = typical::identity;
  template <typename C = continuation>
  struct to
  {
    template <typename T>
    struct inner {
      using type = typical::apply_one<C, T*>;
    };
    template <typename ...T>
    using result = typename inner<T...>::type;
  };
};

template <typename T>
struct wrapped {};

struct wrap
{
  template <typename T>
  using result = wrapped<T>;
};

template <typename F, typename ... Ts>
using apply = typename F::template to<>::template result<Ts...>;
template <typename F, typename C, typename ... Ts>
using apply_to = typename F::template to<C>::template result<Ts...>;

static_assert(std::is_same_v<apply<typical::compose<add_pointer>, int>, int*>);
static_assert(std::is_same_v<apply<typical::compose<add_pointer, add_const>,int>, const int*>);
static_assert(std::is_same_v<apply<typical::compose<add_const, add_pointer>,int>, int*const>);
static_assert(std::is_same_v<apply_to<typical::compose<add_pointer>, wrap, int>, wrapped<int*>>);
static_assert(std::is_same_v<apply_to<typical::compose<add_pointer, add_const>,wrap, int>, wrapped<const int*>>);
