#include <typical/conditional.hpp>

#include <type_traits>

static_assert(std::is_same_v<typical::conditional_t<true, void, char>, void>);
static_assert(std::is_same_v<typical::conditional_t<false, void, char>, char>);

