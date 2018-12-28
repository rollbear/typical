#include <typical/algorithms/size.hpp>
#include <typical/application.hpp>

#include <variant>

using typical::apply_pack;
using typical::apply_pack_to;

static_assert(apply_pack<typical::size, std::variant<int,char,bool>>::value == 3);
static_assert(std::is_same_v<apply_pack_to<typical::size, typical::make<std::tuple>, std::variant<int,char,bool>>, std::tuple<typical::typed_constant<std::size_t, 3>>>);
