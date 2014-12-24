#ifndef XDRPP_LIST_HPP_included
#define XDRPP_LIST_HPP_included

#include "vec_impl.hpp"

#include <list>

namespace xdrpp { namespace detail {

template <typename... Ts> struct xdrer<std::list<Ts...> >
	: vector_xdrer<std::list<Ts...> > {};

} }  // namespace xdrpp::detail

#endif  // XDRPP_LIST_HPP_included
