#ifndef XDRPP_MAP_IMPL_HPP_included
#define XDRPP_MAP_IMPL_HPP_included

#include "base.hpp"

namespace xdrpp { namespace detail {

template <typename Map>
struct map_xdrer
{
	typedef Map value_type;

	static bool encode(XDR* xdrs, Map& map)
	{
		uint32_t size = map.size();
		if (!xdr(xdrs, size))
			return false;
		for (auto& entry : map) {
			typedef typename Map::key_type KeyType;
			if (!xdr(xdrs, const_cast<KeyType&>(entry.first)))
				return false;
			if (!xdr(xdrs, entry.second))
				return false;
		}
		return true;
	}

	static bool decode(XDR* xdrs, Map& map)
	{
		uint32_t size;
		if (!xdr(xdrs, size))
			return false;
		for (uint32_t i = 0; i < size; ++i) {
			typename Map::key_type key;
			if (!xdr(xdrs, key))
				return false;
			if (!xdr(xdrs, map[key]))
				return false;
		}
		return true;
	}
};

} }  // namespace xdrpp::detail

#endif  // XDRPP_MAP_IMPL_HPP_included
