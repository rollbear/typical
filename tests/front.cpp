#include <typical/algorithms/front.hpp>
#include <typical/application.hpp>

using typical::apply_pack;
using typical::apply_pack_to;

static_assert(std::is_same_v<apply_pack<typical::front, void, int, char>, void>);
static_assert(std::is_same_v<apply_pack_to<typical::front, typical::make<std::tuple>, int, char, void>,
  std::tuple<int>>);
