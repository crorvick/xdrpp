#include "string.hpp"

#include <sstream>
#include <algorithm>
#include <cstdint>

namespace xdrpp { namespace impl {

bool string_xdrer::encode(XDR* xdrs, std::string& s)
{
	uint32_t size = s.length();
	uint32_t pad = (size | 0x03) - size + 1;
	char zeros[] = { 0, 0, 0, 0 };

	return xdr(xdrs, size)
	    && xdrs->x_ops->x_putbytes(xdrs, s.c_str(), size)
	    && xdrs->x_ops->x_putbytes(xdrs, zeros, pad);
}

bool string_xdrer::decode(XDR* xdrs, std::string& s)
{
	uint32_t size;

	if (!xdr(xdrs, size))
		return false;

	uint32_t pad = (size | 0x03) - size + 1;
	char buf[BUFSIZ];

	std::ostringstream ss;
	while (size) {
		uint32_t sz = std::min<uint32_t>(size, sizeof (buf));
		if (!xdrs->x_ops->x_getbytes(xdrs, buf, sz))
			return false;
		ss.write(buf, sz);
		size -= sz;
	}
	if (!xdrs->x_ops->x_getbytes(xdrs, buf, pad))
		return false;
	s = ss.str();
	return true;
}

} }  // namespace xdr::impl
