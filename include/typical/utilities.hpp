#ifndef TYPICAL_UTILITIES_HPP
#define TYPICAL_UTILITIES_HPP

namespace typical
{
namespace detail
{
static constexpr unsigned log2(unsigned n, unsigned b = 16)
{
  if (n <= 1) return 0;
  const auto hm = ~((1U << b) - 1U);
  return n & hm ? b + detail::log2(n >> b, b >> 1) : detail::log2(n, b >> 1);
}

template <typename T>
struct proxy;

}
}
#endif //TYPICAL_UTILITIES_HPP
