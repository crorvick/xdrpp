#ifndef XDRPP_PAIR_HPP_included
#define XDRPP_PAIR_HPP_included

#include "base.hpp"

#include <utility>

namespace xdrpp {

template <typename T, typename U>
bool xdr(XDR* xdrs, std::pair<T, U>& p)
{
	return xdr(xdrs, p.first) && xdr(xdrs, p.second);
}

}  // namespace xdrpp

#endif  // XDRPP_PAIR_HPP_included
