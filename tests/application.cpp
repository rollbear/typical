#include <typical/application.hpp>
#include <variant>

struct count
{
  using continuation = typical::identity;
  template <typename C = continuation>
  struct to {
    template <typename ...T>
    using result = typical::apply_one<C, typical::constant<sizeof...(T)>>;
  };
};

static_assert(std::is_same_v<typical::apply_pack<typical::unwrap, std::tuple<int,char,bool>>,
  typical::list<int,char,bool>>);
static_assert(std::is_same_v<typical::apply_pack_to<typical::unwrap, typical::make<std::variant>, std::tuple<int,char,bool>>,
  std::variant<int,char,bool>>);

static_assert(std::is_same_v<typical::apply_list<count, std::variant<int,bool,double>>,
  typical::constant<std::size_t(3)>>);
static_assert(std::is_same_v<typical::apply_list_to<count, typical::make<std::tuple>, std::variant<int,bool,double>>,
  std::tuple<typical::constant<std::size_t(3)>>>);
