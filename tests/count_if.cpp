#include <typical/algorithms/count_if.hpp>

#include <typical/type_predicates.hpp>

using typical::apply_pack;
using typical::apply_pack_to;

static_assert(std::is_same_v<apply_pack<typical::count_if<typical::is_pointer>,int,int*,void*,double>,
              typical::constant<2>>);
static_assert(std::is_same_v<apply_pack<typical::count_if<typical::is_reference>,int,int*,void*,double>,
              typical::constant<0>>);
static_assert(std::is_same_v<apply_pack<typical::count_if<typical::is_same<int>>,int,int*,void*,double>,
              typical::constant<1>>);

static_assert(std::is_same_v<apply_pack<typical::count_if<typical::is_same<int>>>,
  typical::constant<0>>);

static_assert(std::is_same_v<apply_pack_to<typical::count_if<typical::is_same<int>>,typical::make<std::tuple>, int,int*,void*,double>,
  std::tuple<typical::constant<1>>>);
