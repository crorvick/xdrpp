#ifndef XDRPP_STRING_HPP_included
#define XDRPP_STRING_HPP_included

#include "base.hpp"

#include <string>

namespace xdrpp {

bool xdr(XDR* xdrs, std::string&);

}  // namespace xdrpp

#endif  // XDRPP_STRING_HPP_included
