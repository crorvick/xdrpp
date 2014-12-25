#ifndef XDRPP_DEQUE_HPP_included
#define XDRPP_DEQUE_HPP_included

#include "vec_impl.hpp"

#include <deque>

namespace xdrpp { namespace impl {

template <typename... Ts> struct xdrer<std::deque<Ts...> >
	: vector_xdrer<std::deque<Ts...> > {};

} }  // namespace xdrpp::impl

#endif  // XDRPP_DEQUE_HPP_included
