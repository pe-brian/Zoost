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

#include <Zoost/Converter.hpp>
#include <string>

namespace zin
{

////////////////////////////////////////////////////////////
std::string toDigitTime(Uint32 ms)
{
    Uint32 s = ms/1000;
    Uint32 m = s/60;
    Uint32 h = m /60;

    return std::string((h%99 < 10 ? "0" : "") + toString(h%99) + ":" + (m%60 < 10 ? "0" : "") + toString(m%60) + ":" + (s%60 < 10 ? "0" : "") + toString(s%60));
}

////////////////////////////////////////////////////////////
double toRads(double degres)
{
    return degres * 3.141592654f / 180.f;
}

////////////////////////////////////////////////////////////
double toDegres(double rads)
{
    return rads * 180.f / 3.141592654f;
}

}