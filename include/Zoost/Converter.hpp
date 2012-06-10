////////////////////////////////////////////////////////////
//
// Zoost C++ library
// Copyright (C) 2011-2012 Pierre-Emmanuel BRIAN (zinlibs@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef ZOOST_CONVERTER_HPP
#define ZOOST_CONVERTER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <string>
#include <sstream>
#include <Zoost/Config.hpp>

namespace zin
{

////////////////////////////////////////////////////////////
// Convert T to string
////////////////////////////////////////////////////////////
template <typename T>
std::string toString(const T& i)
{
    std::ostringstream stream;
    stream << i;
    return stream.str();
}

////////////////////////////////////////////////////////////
// Convert string to T
////////////////////////////////////////////////////////////
template <typename T>
T fromString(const std::string& str)
{
    std::istringstream stream(str);
    T tmp;
    stream >> tmp;
    return tmp;
}

////////////////////////////////////////////////////////////
// Convert milliseconds uint32 to digit time string
////////////////////////////////////////////////////////////
std::string toDigitTime(Uint32 ms);

////////////////////////////////////////////////////////////
// Convert degres to rads
////////////////////////////////////////////////////////////
double toRads(double degres);

////////////////////////////////////////////////////////////
// Convert rads to degres
////////////////////////////////////////////////////////////
double toDegres(double rads);

}

#endif // ZOOST_CONVERTER_HPP
	

