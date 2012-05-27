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

#include <Zoost/Segment.hpp>

namespace zin
{

////////////////////////////////////////////////////////////
Segment::Segment(const Point& point1, const Point& point2) :
p1(point1),
p2(point2) {}
    
////////////////////////////////////////////////////////////
double Segment::length() const
{
    return Vector2d::length(p2 - p1);
}
    
////////////////////////////////////////////////////////////
Point Segment::operator[](double factor) 
{
    return Point(Math::interpolate(p1.x, p2.x, factor), Math::interpolate(p1.y, p2.y, factor));
}
    
////////////////////////////////////////////////////////////
bool Segment::intersects(const Segment& segment)
{
    Point result;
	return intersects(segment, result);
}

////////////////////////////////////////////////////////////
bool Segment::intersects(const Segment& segment, Point& result)
{ 
	if( !Line(p1, p2).intersects(Line(segment.p1, segment.p2), result) )
	    return false;
	
	return Vector2d::length(result -         p1) + Vector2d::length(result -         p2) >=         length() - .1f
	    && Vector2d::length(result -         p1) + Vector2d::length(result -         p2) <=         length() + .1f
	    && Vector2d::length(result - segment.p1) + Vector2d::length(result - segment.p2) >= segment.length() - .1f
	    && Vector2d::length(result - segment.p1) + Vector2d::length(result - segment.p2) <= segment.length() + .1f;
}

////////////////////////////////////////////////////////////
bool Segment::intersects(const Point& point1, const Point& point2, const Point& point3, const Point& point4)
{
    Segment segment1(point1, point2), segment2(point2, point3);
    return segment1.intersects(segment2);
}

////////////////////////////////////////////////////////////
bool Segment::intersects(const Point& point1, const Point& point2, const Point& point3, const Point& point4, Point& result)
{
    Segment segment1(point1, point2), segment2(point2, point3);
    return segment1.intersects(segment2, result);
}

}