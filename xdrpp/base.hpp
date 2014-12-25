#ifndef XDRPP_BASE_HPP_included
#define XDRPP_BASE_HPP_included

#include <rpc/xdr.h>

namespace xdrpp {

struct XDR_Base : public XDR
{
	XDR_Base(xdr_op);

	virtual bool get(int32_t&);
	virtual bool put(int32_t);
	virtual bool get(char*, size_t) = 0;
	virtual bool put(const char*, size_t) = 0;
	virtual size_t get_position() const = 0;
	virtual bool set_position(size_t) = 0;
	virtual char* get_inline(size_t) { return 0; }

	virtual ~XDR_Base() {}
};

namespace impl {

	template <typename T>
	struct xdrer
	{
		typedef T value_type;

		static bool encode(XDR* xdrs, T& v)
		{
			return v.xdr(v);
		}

		static bool decode(XDR* xdrs, T& v)
		{
			return v.xdr(v);
		}
	};

}  // namespace impl

template <typename T>
bool xdr(XDR* xdrs, T& v)
{
	switch (xdrs->x_op) {
	case XDR_ENCODE: return impl::xdrer<T>::encode(xdrs, v);
	case XDR_DECODE: return impl::xdrer<T>::decode(xdrs, v);
	default:
		break;
	}

	return false;
}

namespace impl {

	template <typename T, bool_t (*f)(XDR*, T*)>
	struct xdr_wrapper
	{
		typedef T value_type;

		static bool encode(XDR* xdrs, T& v)
		{
			return f(xdrs, &v);
		}

		static bool decode(XDR* xdrs, T& v)
		{
			return f(xdrs, &v);
		}
	};

	template <> struct xdrer<char>
		: xdr_wrapper<char, xdr_char> {};

	template <> struct xdrer<short>
		: xdr_wrapper<short, xdr_short> {};

	template <> struct xdrer<int>
		: xdr_wrapper<int, xdr_int> {};

	template <> struct xdrer<long>
		: xdr_wrapper<long, xdr_long> {};

	template <> struct xdrer<unsigned char>
		: xdr_wrapper<unsigned char, xdr_u_char> {};

	template <> struct xdrer<unsigned short>
		: xdr_wrapper<unsigned short, xdr_u_short> {};

	template <> struct xdrer<unsigned int>
		: xdr_wrapper<unsigned int, xdr_u_int> {};

	template <> struct xdrer<unsigned long>
		: xdr_wrapper<unsigned long, xdr_u_long> {};

	template <> struct xdrer<float>
		: xdr_wrapper<float, xdr_float> {};

	template <> struct xdrer<double>
		: xdr_wrapper<double, xdr_double> {};

}

}  // namespace xdrpp

#endif  // XDRPP_BASE_HPP_included
