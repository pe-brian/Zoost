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

#ifndef ZOOST_MATH_HPP
#define ZOOST_MATH_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cmath>
#include <Zoost/Vector2.hpp>
#include <Zoost/Config.hpp>

namespace zin
{

namespace Math
{

////////////////////////////////////////////////////////////
// Get the factorial of the given integer
////////////////////////////////////////////////////////////
unsigned int ZOOST_API fact(unsigned int n);

////////////////////////////////////////////////////////////
// Get the binomial coefficient according to n and k
////////////////////////////////////////////////////////////
unsigned int ZOOST_API binCoef(unsigned int n, unsigned int k);

////////////////////////////////////////////////////////////
// Get the Bernstein result 
////////////////////////////////////////////////////////////
double ZOOST_API bernstein(unsigned int k, unsigned int n, double t);

////////////////////////////////////////////////////////////
// Get the square of the number
////////////////////////////////////////////////////////////
template <typename T>
T ZOOST_API square(T value)
{
    return value * value;
}

////////////////////////////////////////////////////////////
// Get the absolute result of the given value
////////////////////////////////////////////////////////////
template <typename T>
T ZOOST_API abs(T value)
{
	return value < 0 ? -value : value;
}

////////////////////////////////////////////////////////////
// Compute the interpolation from the limits and the coeff t
////////////////////////////////////////////////////////////
template <typename T>
T ZOOST_API interpolate(const T& value1, const T& value2, double t)
{
	if( t > 1.f ) t = 1.f;
	if( t < 0.f ) t = 0.f;
	
	return static_cast<T>(value1 + (value2 - value1) * t);
}

}

}

#endif // ZOOST_MATH_HPP