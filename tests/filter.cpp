#include <typical/algorithms/filter.hpp>

#include <typical/type_predicates.hpp>

using typical::apply_pack;
using typical::apply_pack_to;


static_assert(std::is_same_v<apply_pack<typical::filter<typical::is_pointer>, int, void*, int*, double, char*>,
  typical::list<void*, int*, char*>>);
static_assert(std::is_same_v<apply_pack<typical::filter<typical::is_pointer>>,
  typical::list<>>);

static_assert(std::is_same_v<apply_pack<typical::filter<typical::is_pointer>, int, void, double, char, bool>,
  typical::list<>>);

static_assert(std::is_same_v<apply_pack_to<typical::filter<typical::is_pointer>, typical::make<std::tuple>, int, void*, double*, char, bool>,
  std::tuple<void*, double*>>);
