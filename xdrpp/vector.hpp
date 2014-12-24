#ifndef XDRPP_VECTOR_HPP_included
#define XDRPP_VECTOR_HPP_included

#include "vec_impl.hpp"

#include <vector>

namespace xdrpp { namespace detail {

template <typename... Ts> struct xdrer<std::vector<Ts...> >
	: vector_xdrer<std::vector<Ts...> > {};

} }  // namespace xdrpp::detail

#endif  // XDRPP_VECTOR_HPP_included
