#ifndef XDRPP_H_included
#define XDRPP_H_included

#include <rpc/xdr.h>

#include <string>
#include <vector>
#include <deque>
#include <map>

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

namespace detail {

	template <typename Vector>
	bool xdr_encode_vec(XDR* xdrs, Vector& vec)
	{
		uint32_t size = vec.size();
		if (!xdr(xdrs, size))
			return false;
		for (size_t i = 0; i < size; ++i) {
			if (!xdr(xdrs, vec[i]))
				return false;
		}
		return true;
	}

	template <typename Vector>
	bool xdr_decode_vec(XDR* xdrs, Vector& vec)
	{
		uint32_t size;
		if (!xdr(xdrs, size))
			return false;
		vec.resize(size);
		for (size_t i = 0; i < size; ++i) {
			if (!xdr(xdrs, vec[i]))
				return false;
		}
		return true;
	}

}  // namespace detail

template <typename T>
bool xdr(XDR* xdrs, std::vector<T>& vec)
{
	switch (xdrs->x_op) {
	case XDR_ENCODE: return detail::xdr_encode_vec(xdrs, vec);
	case XDR_DECODE: return detail::xdr_decode_vec(xdrs, vec);
	default:
		break;
	}

	return false;
}

template <typename T>
bool xdr(XDR* xdrs, std::deque<T>& deq)
{
	switch (xdrs->x_op) {
	case XDR_ENCODE: return detail::xdr_encode_vec(xdrs, deq);
	case XDR_DECODE: return detail::xdr_decode_vec(xdrs, deq);
	default:
		break;
	}

	return false;
}

template <typename T, typename U>
bool xdr(XDR* xdrs, std::pair<T, U>& p)
{
	return xdr(xdrs, p.first) && xdr(xdrs, p.second);
}

namespace detail {

	template <typename Map>
	bool xdr_encode_map(XDR* xdrs, Map& map)
	{
		uint32_t size = map.size();
		if (!xdr(xdrs, size))
			return false;
		for (auto& entry : map) {
			if (!xdr(xdrs, entry))
				return false;
		}
		return true;
	}

	template <typename Map>
	bool xdr_decode_map(XDR* xdrs, Map& map)
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

}  // namespace detail

template <typename T, typename U>
bool xdr(XDR* xdrs, std::map<T, U>& map)
{
	switch (xdrs->x_op) {
	case XDR_ENCODE: return detail::xdr_encode_map(xdrs, map);
	case XDR_DECODE: return detail::xdr_decode_map(xdrs, map);
	default:
		break;
	}

	return false;
}

template <typename T, typename U>
bool xdr(XDR* xdrs, std::multimap<T, U>& map)
{
	switch (xdrs->x_op) {
	case XDR_ENCODE: return detail::xdr_encode_map(xdrs, map);
	case XDR_DECODE: return detail::xdr_decode_map(xdrs, map);
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
