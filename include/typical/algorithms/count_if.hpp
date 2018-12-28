#ifndef TYPICAL_COUNT_IF_HPP
#define TYPICAL_COUNT_IF_HPP

#include <typical/function_support.hpp>
#include <typical/application.hpp>

namespace typical
{
template<typename P>
struct count_if {
  using continuation = identity;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;

    template<auto ... Is>
    static constexpr auto sum = (0 + ...  + Is);

    template<typename T>
    using eval = apply_pack<P, T>;
    template<typename ...Ts>
    using result = typename TO::template result<constant<sum<eval<Ts>::value...>>>;
  };
};

}
#endif //TYPICAL_COUNT_IF_HPP
