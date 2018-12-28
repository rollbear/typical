#ifndef TYPICAL_TYPE_TRAITS_HPP
#define TYPICAL_TYPE_TRAITS_HPP

#include <typical/function_support.hpp>
#include <typical/compose.hpp>

namespace typical
{
using add_pointer = from_type<std::add_pointer>;
using add_lvalue_reference = from_type<std::add_lvalue_reference>;
using add_rvalue_reference = from_type<std::add_rvalue_reference>;
using add_const = from_type<std::add_const>;
using add_volatile = from_type<std::add_volatile>;
using remove_reference = from_type<std::remove_reference>;
using remove_pointer = from_type<std::remove_pointer>;
using remove_const = from_type<std::remove_const>;
using remove_volatile = from_type<std::remove_volatile>;
using remove_cv = compose<remove_volatile,remove_const>;
using remove_cv_ref = compose<remove_cv, remove_reference>;


}
#endif //TYPICAL_TYPE_TRAITS_HPP
