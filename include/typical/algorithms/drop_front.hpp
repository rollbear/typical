/*
 * typical - C++ template meta programming library
 *
 * Copyright Björn Fahller 2018,2019
 *
 *  Use, modification and distribution is subject to the
 *  Boost Software License, Version 1.0. (See accompanying
 *  file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt)
 *
 * Project home: https://github.com/rollbear/typical
 */


#ifndef TYPICAL_DROP_FRONT_HPP
#define TYPICAL_DROP_FRONT_HPP

#include <typical/function_support.hpp>
#include <typical/utilities.hpp>

namespace typical
{
namespace detail {
  template<std::size_t>
  using make_voidptr = void*;

  template<typename TO, std::size_t N>
  struct drop_front_helper
  {
    template <typename> struct inner;
    template <std::size_t ... Is>
    struct inner<std::index_sequence<Is...>>
    {
      template <typename ... Ts>
      static typename TO::template result<Ts...> func(make_voidptr<Is>..., detail::proxy<Ts> *...);
    };
    template <typename ... Ts>
    using type = decltype(inner<std::make_index_sequence<N>>::func(static_cast<detail::proxy<Ts>*>(nullptr)...));
  };

  template<typename TO>
  struct drop_front_helper<TO, 0>
  {
    template<typename ... Ts>
    using type = typename TO::template result<Ts...>;
  };

  template<typename TO>
  struct drop_front_helper<TO, 1>
  {
    template <typename ... Ts>
    static typename TO::template result<Ts...> func(void*, detail::proxy<Ts>*...);
    template<typename ... Ts>
    using type = decltype(func(static_cast<detail::proxy<Ts>*>(nullptr)...));
  };

  template<typename TO>
  struct drop_front_helper<TO, 2>
  {
    template <typename ... Ts>
    static typename TO::template result<Ts...> func(void*, void*, detail::proxy<Ts>*...);
    template<typename ... Ts>
    using type = decltype(func(static_cast<detail::proxy<Ts>*>(nullptr)...));
  };

  template<typename TO>
  struct drop_front_helper<TO, 3>
  {
    template <typename ... Ts>
    static typename TO::template result<Ts...> func(void*, void*, void*, detail::proxy<Ts>*...);
    template<typename ... Ts>
    using type = decltype(func(static_cast<detail::proxy<Ts>*>(nullptr)...));
  };

  template<typename TO>
  struct drop_front_helper<TO, 4>
  {
    template <typename ... Ts>
    static typename TO::template result<Ts...> func(void*, void*, void*, void*, detail::proxy<Ts>*...);
    template<typename ... Ts>
    using type = decltype(func(static_cast<detail::proxy<Ts>*>(nullptr)...));
  };

  template<typename TO>
  struct drop_front_helper<TO, 5>
  {
    template <typename ... Ts>
    static typename TO::template result<Ts...> func(void*, void*, void*, void*, void*, detail::proxy<Ts>*...);
    template<typename ... Ts>
    using type = decltype(func(static_cast<detail::proxy<Ts>*>(nullptr)...));
  };

    template<typename TO>
  struct drop_front_helper<TO, 6>
  {
    template <typename ... Ts>
    static typename TO::template result<Ts...> func(void*, void*, void*, void*, void*, void*, detail::proxy<Ts>*...);
    template<typename ... Ts>
    using type = decltype(func(static_cast<detail::proxy<Ts>*>(nullptr)...));
  };

  template<typename TO>
  struct drop_front_helper<TO, 7>
  {
    template <typename ... Ts>
    static typename TO::template result<Ts...> func(void*, void*, void*, void*, void*, void*, void*, detail::proxy<Ts>*...);
    template<typename ... Ts>
    using type = decltype(func(static_cast<detail::proxy<Ts>*>(nullptr)...));
  };

    template<typename TO>
  struct drop_front_helper<TO, 8>
  {
    template <typename ... Ts>
    static typename TO::template result<Ts...>
    func(void*, void*, void*, void*, void*, void*, void*, void*, detail::proxy<Ts>*...);
    template<typename ... Ts>
    using type = decltype(func(static_cast<detail::proxy<Ts>*>(nullptr)...));
  };

      template<typename TO>
  struct drop_front_helper<TO, 9>
  {
    template <typename ... Ts>
    static typename TO::template result<Ts...>
    func(void*, void*, void*, void*, void*, void*, void*, void*,
         void*, detail::proxy<Ts>*...);
    template<typename ... Ts>
    using type = decltype(func(static_cast<detail::proxy<Ts>*>(nullptr)...));
  };

        template<typename TO>
  struct drop_front_helper<TO, 10>
  {
    template <typename ... Ts>
    static typename TO::template result<Ts...>
    func(void*, void*, void*, void*, void*, void*, void*, void*,
         void*, void*, detail::proxy<Ts>*...);
    template<typename ... Ts>
    using type = decltype(func(static_cast<detail::proxy<Ts>*>(nullptr)...));
  };

          template<typename TO>
  struct drop_front_helper<TO, 11>
  {
    template <typename ... Ts>
    static typename TO::template result<Ts...>
    func(void*, void*, void*, void*, void*, void*, void*, void*,
         void*, void*, void*, detail::proxy<Ts>*...);
    template<typename ... Ts>
    using type = decltype(func(static_cast<detail::proxy<Ts>*>(nullptr)...));
  };

            template<typename TO>
  struct drop_front_helper<TO, 12>
  {
    template <typename ... Ts>
    static typename TO::template result<Ts...>
    func(void*, void*, void*, void*, void*, void*, void*, void*,
         void*, void*, void*, void*, detail::proxy<Ts>*...);
    template<typename ... Ts>
    using type = decltype(func(static_cast<detail::proxy<Ts>*>(nullptr)...));
  };

              template<typename TO>
  struct drop_front_helper<TO, 13>
  {
    template <typename ... Ts>
    static typename TO::template result<Ts...>
    func(void*, void*, void*, void*, void*, void*, void*, void*,
         void*, void*, void*, void*, void*, detail::proxy<Ts>*...);
    template<typename ... Ts>
    using type = decltype(func(static_cast<detail::proxy<Ts>*>(nullptr)...));
  };

                template<typename TO>
  struct drop_front_helper<TO, 14>
  {
    template <typename ... Ts>
    static typename TO::template result<Ts...>
    func(void*, void*, void*, void*, void*, void*, void*, void*,
         void*, void*, void*, void*, void*, void*, detail::proxy<Ts>*...);
    template<typename ... Ts>
    using type = decltype(func(static_cast<detail::proxy<Ts>*>(nullptr)...));
  };

  template<typename TO>
  struct drop_front_helper<TO, 15>
  {
    template <typename ... Ts>
    static typename TO::template result<Ts...>
    func(void*, void*, void*, void*, void*, void*, void*, void*,
         void*, void*, void*, void*, void*, void*, void*,
         detail::proxy<Ts>*...);
    template<typename ... Ts>
    using type = decltype(func(static_cast<detail::proxy<Ts>*>(nullptr)...));
  };
  template<typename TO>
  struct drop_front_helper<TO, 16>
  {
    template <typename ... Ts>
    static typename TO::template result<Ts...>
    func(void*, void*, void*, void*, void*, void*, void*, void*,
         void*, void*, void*, void*, void*, void*, void*, void*,
         detail::proxy<Ts>*...);
    template<typename ... Ts>
    using type = decltype(func(static_cast<detail::proxy<Ts>*>(nullptr)...));
  };

}

template <typename N>
struct drop_front
{
  using continuation = make<list>;
  template <typename C = continuation>
  struct to {
    using TO = detail::to<C>;

    template <typename ... Ts>
    using result = typename detail::drop_front_helper<TO, N::value>::template type<Ts...>;
  };
};

}
#endif //TYPICAL_DROP_FRONT_HPP
