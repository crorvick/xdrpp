#include "xdrpp.h"

#include <sstream>
#include <algorithm>

#include <cstdio>
#include <cstdint>
#include <arpa/inet.h>

namespace {

	bool xdr_encode_str(XDR* xdrs, std::string& s)
	{
		int32_t size = s.length();
		uint32_t pad = (size | 0x03) - size + 1;
		char zeros[] = { 0, 0, 0, 0 };

		return xdrs->x_ops->x_putint32(xdrs, &size)
		    && xdrs->x_ops->x_putbytes(xdrs, s.c_str(), size)
		    && xdrs->x_ops->x_putbytes(xdrs, zeros, pad);
	}

	bool xdr_decode_str(XDR* xdrs, std::string& s)
	{
		int32_t size;

		if (!xdrs->x_ops->x_getint32(xdrs, &size))
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

namespace {

	bool_t xdr_getlong_callback(XDR* xdrs, long* lp)
	{
		int32_t v;
		bool ret = static_cast<XDR_Base*>(xdrs)->get(v);
		if (ret)
			*lp = v;
		return ret;
	}

	bool_t xdr_putlong_callback(XDR* xdrs, const long* lp)
	{
		int32_t v = *lp;
		return static_cast<XDR_Base*>(xdrs)->put(v);
	}

	bool_t xdr_getbytes_callback(XDR* xdrs, caddr_t addr, u_int len)
	{
		return static_cast<XDR_Base*>(xdrs)->get(addr, len);
	}

	bool_t xdr_putbytes_callback(XDR* xdrs, const char* addr, u_int len)
	{
		return static_cast<XDR_Base*>(xdrs)->put(addr, len);
	}

	u_int xdr_getpostn_callback(const XDR* xdrs)
	{
		return static_cast<const XDR_Base*>(xdrs)->get_position();
	}

	bool_t xdr_setpostn_callback(XDR* xdrs, u_int pos)
	{
		return static_cast<XDR_Base*>(xdrs)->set_position(pos);
	}

	int32_t* xdr_inline_callback(XDR* xdrs, u_int len)
	{
		return reinterpret_cast<int32_t*>(static_cast<XDR_Base*>(xdrs)->get_inline(len));
	}

	void xdr_destroy_callback(XDR* xdrs)
	{
	}

	bool_t xdr_getint32_callback(XDR* xdrs, int32_t* ip)
	{
		return static_cast<XDR_Base*>(xdrs)->get(*ip);
	}

	bool_t xdr_putint32_callback(XDR* xdrs, const int32_t* ip)
	{
		return static_cast<XDR_Base*>(xdrs)->put(*ip);
	}

	struct XDR::xdr_ops xdr_base_ops = {
		&xdr_getlong_callback,
		&xdr_putlong_callback,
		&xdr_getbytes_callback,
		&xdr_putbytes_callback,
		&xdr_getpostn_callback,
		&xdr_setpostn_callback,
		&xdr_inline_callback,
		&xdr_destroy_callback,
		&xdr_getint32_callback,
		&xdr_putint32_callback
	};

}

XDR_Base::
XDR_Base(xdr_op op)
{
	x_op = op;
	x_ops = &xdr_base_ops;
	x_public = 0;
	x_private = 0;
	x_base = 0;
	x_handy = 0;
}

bool XDR_Base::
get(int32_t& v)
{
	int32_t tmp;
	bool ret = get(reinterpret_cast<char*>(&tmp), sizeof (tmp));
	if (ret)
		v = htonl(tmp);
	return ret;
}

bool XDR_Base::
put(int32_t v)
{
	v = htonl(v);
	return put(reinterpret_cast<char*>(&v), sizeof (v));
}
