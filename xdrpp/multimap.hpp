#ifndef XDRPP_MULTIMAP_HPP_included
#define XDRPP_MULTIMAP_HPP_included

#include "map_impl.hpp"

#include <map>

namespace xdrpp { namespace impl {

template <typename... Ts> struct xdrer<std::multimap<Ts...> >
	: map_xdrer<std::multimap<Ts...> > {};

} }  // namespace xdrpp::impl

#endif  // XDRPP_MULTIMAP_HPP_included
