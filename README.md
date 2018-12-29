#`<typical>`

A highly composabl type based C++ template meta programming
library.

This one is in its infancy. Please toy with it, report back,
and contribute to it. Do not (yet) use it in production.

My aim is to make it production ready, perhaps lacking in
functional breadth, but not in quality, very soon. Hopefully
already in January.

Highlights:

* Composable
* C++17
* Fast

It is no secret that this draws heavily on the
[`Kvasir::mpl`](https://github.com/kvasir-io/mpl/) library,
but by adding another level of indirection for the type
functions, it becomes very composable.

|   |                                                      |
|---|------------------------------------------------------|
|Q. |Why type based when [`boost::Hana`](https://boostorg.github.io/hana/) have showed the way with value oriented TMP?|
|A. |Because sometimes manipulating types is exactly what you want to do.                                        |

Example:
```Cpp
using t = apply_pack_to<
              compose<
                  transform<compose<add_const,add_pointer>>,
                  take<constant<2>>
              >,
              make<std::tuple>,
              int,char,double,unsigned
          >;
// t is std::tuple<int* const, char* const>
```
## Convenience types

* `typical::constant<N>`.
   ```Cpp
   template <auto V>
   struct constant {
       static constexpr auto value = V;
   };
   ```
   `typical::constant<V>` is used by type functions that
   return a numerical or boolean result.
   
* `typical::list<Ts...>`
   ```Cpp
   template <typename ...>
   struct list {};
   ```
   `typical::list<...>` is the default result type for all
   type functions that result in more than one type.
   
## Type functions

All type functions operate on one or several types, and
deliver their result to another type function. The default
terminating type functions are:

* `typical::identity`, used by type functions that result in
   one type, and expresses it in verbatim.
* `typical::make<T>`, creates a `T<ts...>`. The default for
  type functions that result in several types is
  `typical::make<typical::list>`.
  
Some type functions accept only one type, other accepts
parameter packs.

## Convenience type functions

These are here to make it easier to work with `typical`.

* `apply_pack<function, params...>`
   Passes `params...` to the type function `function`, which
   presents its result using the default.
* `apply_pack´to<function, result, params...>`, same as above,
   but where `result` takes the place of the default. For
   example, a type function that defaults to produce a
   `typical::list<...>` may instead produce a tuple by calling
  `apply_pack_to<function, make<std::tuple>, params...>`.
* `apply_list<function, type>`, passes the member types of   
   `type` to `function`. `type` can be any type-based template,
   not just `typical::list<...>`, but for example
   `std::tuple<...>`, `std::variant<...>` or a type-list
   from some other TMP library.
* `apply´list´to<function, result, type>`, same as above, but
  where ´`result` is used instead of the default result type.
* `metamorph<T1<types>,T2>` instantiates a template type 
  `T2` with the types of the `T1` instantiation. E.g.
  `metamorph<std::tuple<int,char>, std::variant>` is
  `std::variant<int,char>`.
  
### `typical::is_pointer`


|Arity|Result type|Default continuation|Header|
|-----|-----------|--------------------|------|
|1    |`typical::constant<>`|`typical::identity`|`<typical/type_predicates.hpp>`|

Example:
```Cpp
using t = apply_pack<is_pointer, int>; // t is constant<false>
```

Tells whether its input type is a pointer or not.

### `typical::is_reference`

|Arity|Result type|Default continuation|Header|
|-----|-----------|--------------------|------|
|1    |`typical::constant<>`|`typical::identity`|`<typical/type_predicates.hpp>`|

Example:
```Cpp
using t = apply_pack<is_reference, int&&>; // t is constant<true>
```

Tells whether its input type is a reference or not. Note that
both rvalue-references and lvalue-references are references.

### `typical::is_lvalue_reference`

|Arity|Result type|Default continuation|Header|
|-----|-----------|--------------------|------|
|1    |`typical::constant<>`|`typical::identity`|`<typical/type_predicates.hpp>`|

Example:
```Cpp
using t = apply_pack<is_lvalue_reference, int&&>; // t is constant<false>
```

Tells whether its input type is an lvalue-reference or not.

### `typical::is_rvalue_reference`

|Arity|Result type|Default continuation|Header|
|-----|-----------|--------------------|------|
|1    |`typical::constant<>`|`typical::identity`|`<typical/type_predicates.hpp>`|

Example:
```Cpp
using t = apply_pack<is_rvalue_reference, int&&>; // t is constant<true>
```

Tells whether its input type is an rvalue-reference or not.

### `typical::is_const`

|Arity|Result type|Default continuation|Header|
|-----|-----------|--------------------|------|
|1    |`typical::constant<>`|`typical::identity`|`<typical/type_predicates.hpp>`|

Example:
```Cpp
using t = apply_pack<is_const, int>; // t is constant<false>
```

Tells whether its input type is const or not.

### `typical::is_volatile`

|Arity|Result type|Default continuation|Header|
|-----|-----------|--------------------|------|
|1    |`typical::constant<>`|`typical::identity`|`<typical/type_predicates.hpp>`|

Example:
```Cpp
using t = apply_pack<is_volatile, int volatile>; // t is constant<true>
```

Tells whether its input type is volatile or not.

### `typical::is_template<T<>>`

|Arity|Result type|Default continuation|Header|
|-----|-----------|--------------------|------|
|1    |`typical::constant<>`|`typical::identity`|`<typical/type_predicates.hpp>`|

Example:
```Cpp
using t = apply_pack<is_template<std::tuple>, std::variant<int,char>>; // t is constant<false>
using u = apply_pack<is_template<std::tuple>, std::tuple<int,char>>; // t is constant<true>
```

Tells whether its input type is an instantiation of the searched for
template type or not.

### ´typical::negate<func>`

|Arity|Result type|Default continuation|Header|
|-----|-----------|--------------------|------|
|1    |`typical::constant<>`|`typical::identity`|`<typical/type_predicates.hpp>`|

Example:
```Cpp
using t = apply_pack<negate<is_template<std::tuple>>, std::variant<int,char>>; // t is constant<true>
using u = apply_pack<negate<is_template<std::tuple>>, std::tuple<int,char>>; // t is constant<false>
```
Logically inverts the result of the function.

### `typical::is_same<type>`

|Arity|Result type|Default continuation|Header|
|-----|-----------|--------------------|------|
|1    |`typical::constant<>`|`typical::identity`|`<typical/type_predicates.hpp>`|

Example:
```Cpp
using t = apply_pack<is_same<char>, int>; // t is constant<false>
```
Tells whether its input type is the searched for type or not.

### `typical::add_pointer`

|Arity|Result type|Default continuation|Header|
|-----|-----------|--------------------|------|
|1    |pointer type|`typical::identity`|`<typical/type_manipulation.hpp>`|

Example:
```Cpp
using t = apply_pack<add_pointer, int>; // t is int*
```

Adds pointer to the input type

### `typical::add_lvalue_reference`

|Arity|Result type|Default continuation|Header|
|-----|-----------|--------------------|------|
|1    |reference type|`typical::identity`|`<typical/type_manipulation.hpp>`|

Example:
```Cpp
using t = apply_pack<add_lvalue_reference, int>; // t is int&
```
Adds lvalue-reference to the input type. Note that reference
collapsing rules apply.


### `typical::add_rvalue_reference`

|Arity|Result type|Default continuation|Header|
|-----|-----------|--------------------|------|
|1    |reference type|`typical::identity`|`<typical/type_manipulation.hpp>`|

Example:
```Cpp
using t = apply_pack<add_rvalue_reference, int>; // t is int&&
```
Adds rvalue-reference to the input type. Note that reference
collapsing rules apply.


### `typical::add_const`

|Arity|Result type|Default continuation|Header|
|-----|-----------|--------------------|------|
|1    |reference type|`typical::identity`|`<typical/type_manipulation.hpp>`|

Example:
```Cpp
using t = apply_pack<add_const, int>; // t is int const
```
Adds const to the input type.

### `typical::add_volatile`

|Arity|Result type|Default continuation|Header|
|-----|-----------|--------------------|------|
|1    |reference type|`typical::identity`|`<typical/type_manipulation.hpp>`|

Example:
```Cpp
using t = apply_pack<add_volatile, int>; // t is int volatile
```
Adds volatile to the input type.

### `typical::remove_cv`

|Arity|Result type|Default continuation|Header|
|-----|-----------|--------------------|------|
|1    |unqualified type|`typical::identity`|`<typical/type_manipulation.hpp>`|

Example:
```Cpp
using t = apply_pack<remove_cv, int const volatile>; // t is int
```
Removes const and/or volatile qualifiers from the input type.

### `typical::remove_cv_ref`

|Arity|Result type|Default continuation|Header|
|-----|-----------|--------------------|------|
|1    |unqualified type|`typical::identity`|`<typical/type_manipulation.hpp>`|

Example:
```Cpp
using t = apply_pack<remove_cv_ref, int const volatile&>; // t is int
```
Removes const and/or volatile qualifiers as well as references from the input type.

### `typical::remove_reference`

|Arity|Result type|Default continuation|Header|
|-----|-----------|--------------------|------|
|1    |non-reference type|`typical::identity`|`<typical/type_manipulation.hpp>`|

Example:
```Cpp
using t = apply_pack<remove_reference, int const&&>; // t is int const
```
Removes rvalue-reference or lvalue-reference from the input type.

### `typical::is_empty`

|Arity|Result type|Default continuation|Header|
|-----|-----------|--------------------|------|
|1    |typical::constant<>|`typical::identity`|`<typical/list_predicates.hpp>`|

Example:
```Cpp
using t = apply_pack<is_empty, std::tuple<>>; // t is constant<true>
using f = apply_pack<is_empty, std::variant<int>>; // f is constant<false>
```
Tells whether a variadic template type is instantiated with types or not.

### `typical::any_of<P>`

|Arity|Result type|Default continuation|Header|
|-----|-----------|--------------------|------|
|n    |typical::constant<>|`typical::identity`|`<typical/list_predicates.hpp>`|

Example:
```Cpp
using t = apply_pack<any_of<is_pointer>, int, void*, char>; // t is constant<true>
using f = apply_pack<any_of<is_reference>, int, void*, char>; // f is constant<false>
```
Tells whether any of the types provided matches the predicate `P`

### `typical::all_of<P>`

|Arity|Result type|Default continuation|Header|
|-----|-----------|--------------------|------|
|n    |typical::constant<>|`typical::identity`|`<typical/list_predicates.hpp>`|

Example:
```Cpp
using t = apply_pack<all_of<is_pointer>, int*, void*, char*>; // t is constant<true>
using t = apply_pack<all_of<is_pointer>, int, void*, char>; // f is constant<false>
```
Tells whether all of the types provided matches the predicate `P`

### `typical::none_of<P>`

|Arity|Result type|Default continuation|Header|
|-----|-----------|--------------------|------|
|n    |typical::constant<>|`typical::identity`|`<typical/list_predicates.hpp>`|

Example:
```Cpp
using t = apply_pack<none_of<is_pointer>, int, void, char>; // t is constant<true>
using t = apply_pack<none_of<is_pointer>, int, void*, char>; // f is constant<false>
```
Tells whether none of the types provided matches the predicate `P`

### `typical::has<T>`

|Arity|Result type|Default continuation|Header|
|-----|-----------|--------------------|------|
|n    |typical::constant<>|`typical::identity`|`<typical/list_predicates.hpp>`|

Example:
```Cpp
using t = apply_pack<has<int>, int, void, char>; // t is constant<true>
using t = apply_pack<has<int>, long, void*, char>; // f is constant<false>
```
Tells the type list provided has the searched for type.


### `typical::all_unique`

|Arity|Result type|Default continuation|Header|
|-----|-----------|--------------------|------|
|n    |typical::constant<>|`typical::identity`|`<typical/list_predicates.hpp>`|

Example:
```Cpp
using t = apply_pack<all_unique, int, void, char>; // t is constant<true>
using t = apply_pack<all_unique, long, void, long>; // f is constant<false>
```
Tells the type list provided has only unique types without duplicates.

### `typical::at`

|Arity|Result type|Default continuation|Header|
|-----|-----------|--------------------|------|
|n    |type|`typical::identity`|`<typical/algorithms/at.hpp>`|

Example:
```Cpp
using t = apply_pack<at<constant<1>>, int, void, char>; // t is void
```
Results in the n-th type in the parameter pack. The index can
be any type that has an integral `value` member, e.g.
`typical::constant<N>` or `std::integral_constant<T,v>`

### `typical::count_if`

|Arity|Result type|Default continuation|Header|
|-----|-----------|--------------------|------|
|n    |`typical::constant<>`|`typical::identity`|`<typical/algorithms/count_if.hpp>`|

Example:
```Cpp
using t = apply_pack<count_if<is_const>, int, void, char const, double>; // t is constant<1>
```
Counts the number of parameters in the pack that matches the predicate.

### `typical::drop_front`

|Arity|Result type|Default continuation|Header|
|-----|-----------|--------------------|------|
|n    |list|`typical::make<typical::list>`|`<typical/algorithms/drop_front.hpp>`|

Example:
```Cpp
using t = apply_pack<drop_front<constant<1>>, int, void, char const, double>; // t is list<void,char const, double>
```
Drops the first N parameters from the input pack. The index
type can be any type that has an integral `value` member, e.g.
`typical::constant<N>` or `std::integral_constant<T,v>`.

### `typical::filter`

|Arity|Result type|Default continuation|Header|
|-----|-----------|--------------------|------|
|n    |list|`typical::make<typical::list>`|`<typical/algorithms/filter.hpp>`|

Example:
```Cpp
using t = apply_pack<filter<is_pointer>, int, void*, char*, double>; // t is list<int*, void*>
```
Produces a list of the types that matches the predicate.

### `typical::flatten`

|Arity|Result type|Default continuation|Header|
|-----|-----------|--------------------|------|
|1    |list|`typical::make<typical::list>`|`<typical/algorithms/flatten.hpp>`|

Example:
```Cpp
using t = apply_pack<flatten, tuple<int,variant<double,char>,tuple<duble>>; // t is list<int,variant<double,char>,double>
```
Flattens the hierarchy described by the input template type.
All instantiations of the same basic template are flattened,
whereas instantiations of other templates are untouched.

### `typical::front`

|Arity|Result type|Default continuation|Header|
|-----|-----------|--------------------|------|
|n    |type|`typical::identity`|`<typical/algorithms/front.hpp>`|

Example:
```Cpp
using t = apply_pack<front, int,char,double>; // t is int
```
Produces the first type in the parameter pack

### `typical::index_of`

|Arity|Result type|Default continuation|Header|
|-----|-----------|--------------------|------|
|n    |`typical::constant<>`|`typical::identity`|`<typical/algorithms/index_of.hpp>`|

Example:
```Cpp
using t = apply_pack<index_of<char>, int,char,double>; // t is constant<1>
```
Tells the position of the searched for type in the parameter pack,
or -1 if not found.

### `typical::join`

|Arity|Result type|Default continuation|Header|
|-----|-----------|--------------------|------|
|n    |list|`typical::make<typical::list>`|`<typical/algorithms/join.hpp>`|

Example:
```Cpp
using t = apply_pack<join, tuple<int,char>,tuple<unsigned,double>>; // t is list<int,char,unsigned,double>
```
Joins members of like variadic templates.

### `typical::partition`

|Arity|Result type|Default continuation|Header|
|-----|-----------|--------------------|------|
|n    |list|`typical::make<typical::list>`|`<typical/algorithms/partition.hpp>`|

Example:
```Cpp
using t = apply_pack_to<partition<is_pointer>, make<tuple>, int,char*,unsigned*,double>; // t is tuple<list<char*,unsigned*>,list<int,double>>
```
Partitions the input parameter pack acording to the predicate. Each partition is always
represented by a `typical::list`, but the top-level type depends on
the continuation.

### `typical::reverse`

|Arity|Result type|Default continuation|Header|
|-----|-----------|--------------------|------|
|n    |list|`typical::make<typical::list>`|`<typical/algorithms/reverse.hpp>`|

Example:
```Cpp
using t = apply_pack<reverse, int,char,unsigned,double>; // t is list<double,unsigned,char,int>
```
Presents the input parameter pack in reversed order

### `typical::size`

|Arity|Result type|Default continuation|Header|
|-----|-----------|--------------------|------|
|n    |`typical::constant<>`|`typical::identity`|`<typical/algorithms/size.hpp>`|

Example:
```Cpp
using t = apply_pack<size, int,char,unsigned,double>; // t is constant<4>
```
Presents number of parameters in the input pack

### `typical::take`

|Arity|Result type|Default continuation|Header|
|-----|-----------|--------------------|------|
|n    |list|`typical::make<typical::list>`|`<typical/algorithms/take.hpp>`|

Example:
```Cpp
using t = apply_pack<take<constant<3>>, int,char,unsigned,double>; // t is list<int,char,unsigned>
```
Takes the first N parameters from the input pack. The index
type can be any type that has an integral `value` member, e.g.
`typical::constant<N>` or `std::integral_constant<T,v>`.

### `typical::transform`

|Arity|Result type|Default continuation|Header|
|-----|-----------|--------------------|------|
|n    |list|`typical::make<typical::list>`|`<typical/algorithms/transform.hpp>`|

Example:
```Cpp
using t = apply_pack<transform<add_const>, int,char,unsigned>; // t is list<int const,char const,unsigned const>
```
Instantiates a template with the type function applied to each member
of the input parameter pack.

### `typical::zip`

|Arity|Result type|Default continuation|Header|
|-----|-----------|--------------------|------|
|2    |list|`typical::make<typical::list>`|`<typical/algorithms/zip.hpp>`|

Example:
```Cpp
struct make_pair
{
  using continuation = typical::identity;
  template <typename C = continuation>
  struct to {
    template<typename T, typename U>
    using result = typename C::template result<std::pair<T, U>>;
  };
};
using t = apply_pack<zip<make_pair>, list<int,char>,list<unsigned,double>>; // t is list<pair<int,unsigned>,pair<char,unsigned>>
```
Instantiates a template with the result of applying the provided binary
type function to the element-wise pairs of the two input lists.
N.B. The inputs need not be `typical::list<>`, but must both be
instantiations of variadic templates with the same number of type
parameters.

### `typical::compose`

|Arity|Result type|Default continuation|Header|
|-----|-----------|--------------------|------|
|n    |-|-|`<typical/compose.hpp>`|

Example:
```Cpp
using t = apply_pack<compose<transform<compose<add_const,add_pointer>>,take<constant<2>>>,int,char,double,unsigned> // t is list<int* const, char* const>
```

Create a composition of type functions that applies each of them
with the result from the other. They are applied right to left.
