#ifndef XDRPP_H_included
#define XDRPP_H_included

#include <rpc/xdr.h>

#include <string>
#include <vector>
#include <deque>
#include <list>
#include <map>

namespace xdrpp {

namespace detail {

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

bool xdr(XDR* xdrs, std::string&);

template <typename T>
bool xdr(XDR* xdrs, T& v)
{
	switch (xdrs->x_op) {
	case XDR_ENCODE: return detail::xdrer<T>::encode(xdrs, v);
	case XDR_DECODE: return detail::xdrer<T>::decode(xdrs, v);
	default:
		break;
	}

	return false;
}

namespace detail {

	template <typename Vector>
	struct vector_xdrer
	{
		typedef Vector value_type;

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

	template <typename... Ts> struct xdrer<std::vector<Ts...> >
		: vector_xdrer<std::vector<Ts...> > {};

	template <typename... Ts> struct xdrer<std::deque<Ts...> >
		: vector_xdrer<std::deque<Ts...> > {};

	template <typename... Ts> struct xdrer<std::list<Ts...> >
		: vector_xdrer<std::list<Ts...> > {};

}  // namespace detail

template <typename T, typename U>
bool xdr(XDR* xdrs, std::pair<T, U>& p)
{
	return xdr(xdrs, p.first) && xdr(xdrs, p.second);
}

namespace detail {

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

	template <typename... Ts> struct xdrer<std::map<Ts...> >
		: map_xdrer<std::map<Ts...> > {};

	template <typename... Ts> struct xdrer<std::multimap<Ts...> >
		: map_xdrer<std::multimap<Ts...> > {};

}  // namespace detail

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

}  // namespace xdrpp

#endif  /* XDRPP_H_included */
