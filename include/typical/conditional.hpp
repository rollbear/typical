#ifndef TYPICAL_CONDITIONAL_HPP
#define TYPICAL_CONDITIONAL_HPP

namespace typical
{
template<bool>
struct conditional {
  template<typename T, typename>
  using result = T;
};

template<>
struct conditional<false> {
  template<typename, typename U>
  using result = U;
};

template<bool b, typename T, typename U>
using conditional_t = typename conditional<b>::template result<T, U>;

}

#endif //TYPICAL_CONDITIONAL_HPP
