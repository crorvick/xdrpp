#ifndef XDRPP_STRING_HPP_included
#define XDRPP_STRING_HPP_included

#include "base.hpp"

#include <string>

namespace xdrpp { namespace impl {

struct string_xdrer
{
	typedef std::string value_type;

	static bool encode(XDR* xdrs, std::string& s);
	static bool decode(XDR* xdrs, std::string& s);
};

template <> struct xdrer<std::string> : string_xdrer {};

} }  // namespace xdrpp::impl

#endif  // XDRPP_STRING_HPP_included
