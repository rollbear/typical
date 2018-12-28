#ifndef TYPICAL_TRANSFORM_HPP
#define TYPICAL_TRANSFORM_HPP

#include <typical/function_support.hpp>
#include <typical/application.hpp>

namespace typical
{
template<typename F>
struct transform {
  using continuation = make<list>;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;
    template<typename ... Ts>
    using result = typename TO::template result<apply_pack<F, Ts>...>;
  };
};

}

#endif //TYPICAL_TRANSFORM_HPP
