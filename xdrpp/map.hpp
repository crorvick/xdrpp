#ifndef XDRPP_MAP_HPP_included
#define XDRPP_MAP_HPP_included

#include "map_impl.hpp"

#include <map>

namespace xdrpp { namespace impl {

template <typename... Ts> struct xdrer<std::map<Ts...> >
	: map_xdrer<std::map<Ts...> > {};

} }  // namespace xdrpp::impl

#endif  // XDRPP_MAP_HPP_included
