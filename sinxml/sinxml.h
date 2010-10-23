#ifndef sinxml_h
#define sinxml_h

#include "document.h"
#include "element.h"
#include <sstream>

namespace sinxml
{

template<typename T>
std::string tostring(T& t)
{
	std::stringstream c;
	c<<t;
	std::string s;
	c>>s;
	return s;
}

template<typename T>
T fromstring(const std::string& s)
{
	std::stringstream c;
	c<<s;
	T t;
	c>>t;
	return t;
}

}

#endif
