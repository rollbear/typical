#ifndef TYPICAL_PARTITION_HPP
#define TYPICAL_PARTITION_HPP

#include <typical/function_support.hpp>
#include <typical/application.hpp>
#include <typical/conditional.hpp>
#include <typical/algorithms/join.hpp>

namespace typical
{
template<typename P>
struct partition {
  using continuation = make<list>;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;
    template<typename ... Ts>
    struct helper {
      using type = typename TO::template result<apply_pack_to<join, make<list>, conditional_t<apply_pack<P, Ts>::value, list<Ts>, list<>>...>,
      apply_pack_to<join, make<list>, conditional_t<apply_pack<P, Ts>::value, list<>, list<Ts>>...>>;
    };
    template<typename ... Ts>
    using result = typename helper<Ts...>::type;
  };
};

}
#endif //TYPICAL_PARTITION_HPP
