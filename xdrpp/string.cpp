#include "string.hpp"

#include <sstream>
#include <algorithm>
#include <cstdint>

namespace xdrpp {

namespace {

	bool xdr_encode_str(XDR* xdrs, std::string& s)
	{
		uint32_t size = s.length();
		uint32_t pad = (size | 0x03) - size + 1;
		char zeros[] = { 0, 0, 0, 0 };

		int32_t ssize = size;

		return xdrs->x_ops->x_putint32(xdrs, &ssize)
		    && xdrs->x_ops->x_putbytes(xdrs, s.c_str(), size)
		    && xdrs->x_ops->x_putbytes(xdrs, zeros, pad);
	}

	bool xdr_decode_str(XDR* xdrs, std::string& s)
	{
		int32_t ssize;

		if (!xdrs->x_ops->x_getint32(xdrs, &ssize))
			return false;

		uint32_t size = ssize;
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

}  // anonymous namespace

bool xdr(XDR* xdrs, std::string& s)
{
	switch (xdrs->x_op) {
	case XDR_ENCODE: return xdr_encode_str(xdrs, s);
	case XDR_DECODE: return xdr_decode_str(xdrs, s);
	default:
		break;
	}

	return false;
}

}
