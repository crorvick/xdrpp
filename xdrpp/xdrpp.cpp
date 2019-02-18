#include "base.hpp"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <cstdint>
#include <arpa/inet.h>

namespace xdrpp {

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

#ifdef HAVE_LIBTIRPC
# define GETPOSTN_CV_MODIFIER
#else
# define GETPOSTN_CV_MODIFIER const
#endif

	u_int xdr_getpostn_callback(GETPOSTN_CV_MODIFIER XDR* xdrs)
	{
		return static_cast<GETPOSTN_CV_MODIFIER XDR_Base*>(xdrs)->get_position();
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

	struct xdr_ops_initializer : XDR::xdr_ops
	{
		xdr_ops_initializer()
		{
			x_getlong = &xdr_getlong_callback;
			x_putlong = &xdr_putlong_callback;
			x_getbytes = &xdr_getbytes_callback;
			x_putbytes = &xdr_putbytes_callback;
			x_getpostn = &xdr_getpostn_callback;
			x_setpostn = &xdr_setpostn_callback;
			x_inline = &xdr_inline_callback;
			x_destroy = &xdr_destroy_callback;
		}
	};

	xdr_ops_initializer xdr_base_ops;
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

}  // namespace xdrpp
