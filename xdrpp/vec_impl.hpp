#ifndef XDRPP_VEC_IMPL_HPP_included
#define XDRPP_VEC_IMPL_HPP_included

#include "base.hpp"

namespace xdrpp { namespace impl {

template <typename Vector>
struct vector_xdrer
{
	using value_type = Vector;

	static bool encode(XDR* xdrs, Vector& vec)
	{
		uint32_t size = vec.size();
		if (!xdr(xdrs, size))
			return false;
		for (auto &e : vec) {
			if (!xdr(xdrs, e))
				return false;
		}
		return true;
	}

	static bool decode(XDR* xdrs, Vector& vec)
	{
		uint32_t size;
		if (!xdr(xdrs, size))
			return false;
		vec.resize(size);
		for (auto &e : vec) {
			if (!xdr(xdrs, e))
				return false;
		}
		return true;
	}
};

} }  // namespace xdrpp::impl

#endif  // XDRPP_VEC_IMPL_HPP_included
