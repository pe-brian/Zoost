////////////////////////////////////////////////////////////
//
// Zoost C++ library
// Copyright (C) 2011-2012 ZinLibs (zinlibs@gmail.com)
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

#include <Zoost/Line.hpp>

namespace zin
{

////////////////////////////////////////////////////////////
Line::Line(const Point& point1, const Point& point2) :
p1(point1),
p2(point2) {}

////////////////////////////////////////////////////////////
bool Line::intersects(const Line& line)
{
	return Math::abs(Vector2d::scalarProduct(p2 - p1, line.p2 - line.p1) < Vector2d::length(p2 - p1) * Vector2d::length(line.p2 - line.p1));
}

////////////////////////////////////////////////////////////
bool Line::intersects(const Line& line, Point& result)
{
	if( intersects(line) )
	{
		if( p1.x == p2.x )
		{
			result.x = p1.x;
			result.y = (line.p1.y - line.p2.y) / (line.p1.x - line.p2.x) * (result.x - line.p1.x) + line.p1.y;
		}

		else if( line.p1.x == line.p2.x )
		{
			result.x = line.p1.x;
			result.y = (p1.y - p2.y) / (p1.x - p2.x) * (result.x - p1.x) + p1.y;
		}
		
		else
		{
		    double a1 = (p1.y - p2.y) / (p1.x - p2.x),
                   a2 = (line.p1.y - line.p2.y) / (line.p1.x - line.p2.x),
                   x = (a1 * p1.x - p1.y - a2 * line.p1.x + line.p1.y) / (a1 - a2);

            result = {x, a1 * (x - p1.x) + p1.y};
        }
    
        return true;
	}
	
	return false;
}

////////////////////////////////////////////////////////////
bool intersects(const Point& point1, const Point& point2, const Point& point3, const Point& point4)
{
	Line line1(point1, point2), line2(point3, point4);
	return line1.intersects(line2);
}

////////////////////////////////////////////////////////////
bool intersects(const Point& point1, const Point& point2, const Point& point3, const Point& point4, Point& result)
{
	Line line1(point1, point2), line2(point3, point4);
	return line1.intersects(line2, result);
}

}