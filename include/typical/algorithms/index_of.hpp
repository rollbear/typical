#ifndef TYPICAL_INDEX_OF_HPP
#define TYPICAL_INDEX_OF_HPP

#include <typical/application.hpp>
#include <typical/utilities.hpp>

// TODO: Requires that the searched for type only exists once. Fix that!

namespace typical
{
template <typename T>
struct index_of
{
  template <std::size_t ... Is, typename ... Ts>
  static constexpr auto index_func(std::index_sequence<Is...>, detail::proxy<Ts>*...)
  {
    constexpr auto i = (((std::is_same_v<T,Ts>*(Is+1)) + ... + 0));
    return int(i)-1;
  }
  template <typename ... Ts>
  static constexpr auto index_func(detail::proxy<Ts>*... p)
  {
    return index_func(std::index_sequence_for<Ts...>{}, p...);
  }

  using continuation = identity;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;

    template <typename ... Ts>
    using result = apply_one<TO,constant<index_func(static_cast<detail::proxy<Ts>*>(nullptr)...)>>;
  };
};

}
#endif //TYPICAL_INDEX_OF_HPP
