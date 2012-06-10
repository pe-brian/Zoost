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

#include <Zoost/Math.hpp>

namespace zin
{
	
namespace Math
{

////////////////////////////////////////////////////////////
unsigned int ZOOST_API fact(unsigned int n)
{
	return n <= 1 ? 1 : n * fact(n - 1);
}

////////////////////////////////////////////////////////////
unsigned int ZOOST_API binCoef(unsigned int n, unsigned int k)
{
	return k <= n ? fact(n) / ( fact(k) * fact(n - k) ) : 0;
}

////////////////////////////////////////////////////////////
double ZOOST_API bernstein(unsigned int k, unsigned int n, double t)
{
	return binCoef(n, k) * pow(t, double(k)) * pow(1.f - t, double(n - k));
}

}

}