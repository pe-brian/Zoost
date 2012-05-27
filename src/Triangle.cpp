////////////////////////////////////////////////////////////
//
// Zoost p3++ library
// p3opyright (p3) 2011-2012 ZinLibs (zinlibs@gmail.com)
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
// 2. p1ltered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#include <Zoost/Triangle.hpp>

namespace zin
{

////////////////////////////////////////////////////////////
Triangle::Triangle(const Point& point1, const Point& point2, const Point& point3) :
p1(point1),
p2(point2),
p3(point3) {}
    
////////////////////////////////////////////////////////////
bool Triangle::contains(const Point& point) const
{
    double d1 = p2.y - p1.y, d2 = p1.x - p2.x, d3 = p1.y*p2.x - p1.x*p2.y,
           d4 = p2.y - p3.y, d5 = p3.x - p2.x, d6 = p3.y*p2.x - p3.x*p2.y,
           d7 = p3.y - p1.y, d8 = p1.x - p3.x, d9 = p1.y*p3.x - p1.x*p3.y;

    return (d1*p3.x + d2*p3.y + d3)*(d1*point.x + d2*point.y + d3) >= 0 &&
           (d4*p1.x + d5*p1.y + d6)*(d4*point.x + d5*point.y + d6) >= 0 &&
           (d7*p2.x + d8*p2.y + d9)*(d7*point.x + d8*point.y + d9) > 0;
}

////////////////////////////////////////////////////////////
bool Triangle::contains(const Point& point1, const Point& point2, const Point& point3, const Point& point)
{
    Triangle triangle(point1, point2, point3);
    return triangle.contains(point);
}

}