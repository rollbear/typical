#include <typical/algorithms/zip.hpp>

#include <variant>

using typical::apply_pack;
using typical::apply_pack_to;

struct make_pair
{
  using continuation = typical::identity;
  template <typename C = continuation>
  struct to {
    template<typename T, typename U>
    using result = typename C::template result<std::pair<T, U>>;
  };
};

static_assert(std::is_same_v<apply_pack<typical::zip<::make_pair>, std::tuple<int,char>, std::variant<bool,double>>,
  typical::list<std::pair<int,bool>, std::pair<char,double>>>);
static_assert(std::is_same_v<apply_pack<typical::zip<::make_pair>, std::tuple<>, std::variant<>>,
  typical::list<>>);
static_assert(std::is_same_v<apply_pack_to<typical::zip<::make_pair>, typical::make<std::tuple>, std::tuple<int,char>, std::variant<bool,double>>,
  std::tuple<std::pair<int,bool>, std::pair<char,double>>>);
