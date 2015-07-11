#ifndef XDRPP_PAIR_HPP_included
#define XDRPP_PAIR_HPP_included

#include "base.hpp"

#include <utility>

namespace xdrpp { namespace impl {

template <typename T, typename U>
struct xdrer<std::pair<T, U> >
{
	using value_type = std::pair<T, U>;

	static bool encode(XDR* xdrs, std::pair<T, U>& p)
	{
		return xdr(xdrs, p.first) && xdr(xdrs, p.second);
	}

	static bool decode(XDR* xdrs, std::pair<T, U>& p)
	{
		return xdr(xdrs, p.first) && xdr(xdrs, p.second);
	}
};

} }  // namespace xdrpp::impl

#endif  // XDRPP_PAIR_HPP_included
