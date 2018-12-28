#include <typical/algorithms/transform.hpp>
#include <typical/type_manipulation.hpp>
#include <typical/application.hpp>

using typical::apply_pack;

static_assert(std::is_same_v<apply_pack<typical::transform<typical::add_pointer>, int,char,double>,
              typical::list<int*,char*,double*>>);
static_assert(std::is_same_v<apply_pack<typical::transform<typical::add_pointer>>, typical::list<>>);
static_assert(std::is_same_v<apply_pack<typical::compose<typical::transform<typical::add_pointer>, typical::unwrap>, std::tuple<int,char,double>>, typical::list<int*,char*,double*>>);
