#ifndef TYPICAL_FRONT_HPP
#define TYPICAL_FRONT_HPP

#include <typical/function_support.hpp>
#include <typical/utilities.hpp>

namespace typical
{
struct front {
  using continuation = identity;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;
    template<typename T>
    static apply_one<TO, T> func(detail::proxy<T> *, ...);

    template<typename ... Ts>
    using result = decltype(func(static_cast<detail::proxy<Ts> *>(nullptr)...));
  };
};



}
#endif //TYPICAL_FRONT_HPP
