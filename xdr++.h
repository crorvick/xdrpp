#ifndef XDRPP_H_included
#define XDRPP_H_included

#include <rpc/xdr.h>

#include <string>
#include <vector>

inline bool xdr(XDR* xdrs, char& v) { return xdr_char(xdrs, &v); }
inline bool xdr(XDR* xdrs, short& v) { return xdr_short(xdrs, &v); }
inline bool xdr(XDR* xdrs, int& v) { return xdr_int(xdrs, &v); }
inline bool xdr(XDR* xdrs, long& v) { return xdr_long(xdrs, &v); }
inline bool xdr(XDR* xdrs, unsigned char& v) { return xdr_u_char(xdrs, &v); }
inline bool xdr(XDR* xdrs, unsigned short& v) { return xdr_u_short(xdrs, &v); }
inline bool xdr(XDR* xdrs, unsigned int& v) { return xdr_u_int(xdrs, &v); }
inline bool xdr(XDR* xdrs, unsigned long& v) { return xdr_u_long(xdrs, &v); }
inline bool xdr(XDR* xdrs, float& v) { return xdr_float(xdrs, &v); }
inline bool xdr(XDR* xdrs, double& v) { return xdr_double(xdrs, &v); }

bool xdr(XDR* xdrs, std::string&);

template <typename T>
bool xdr(XDR* xdrs, std::vector<T>& v)
{
	uint32_t size;

	switch (xdrs->x_op) {
	case XDR_ENCODE:
		size = v.size();
		if (!xdr(xdrs, size))
			return false;
		for (size_t i = 0; i < size; ++i) {
			if (!xdr(xdrs, v[i]))
				return false;
		}
		return true;

	case XDR_DECODE:
		if (!xdr(xdrs, size))
			return false;
		v.resize(size);
		for (size_t i = 0; i < size; ++i) {
			if (!xdr(xdrs, v[i]))
				return false;
		}
		return true;

	default:
		break;
	}

	return false;
}

template <typename T>
inline bool xdr(XDR* xdrs, const T& v)
{
	return xdrs->x_op == XDR_ENCODE && xdr(xdrs, const_cast<T&>(v));
}

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

#endif  /* XDRPP_H_included */
