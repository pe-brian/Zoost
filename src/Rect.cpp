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

#include <Zoost/Rect.hpp>

namespace zin
{
    
////////////////////////////////////////////////////////////
Rect::Rect(const Point& p, const Vector2d& s) :
pos(p),
size(s)
{
    if( size.x <= 0 )
        size.x = 1;

    if( size.y <= 0 )
        size.y = 1;
}

////////////////////////////////////////////////////////////
bool Rect::contains(const Point& point) const
{
    return (point.x >= pos.x) && (point.x < pos.x + size.x) && (point.y >= pos.y) && (point.y < pos.y + size.y);
}

////////////////////////////////////////////////////////////
bool Rect::intersects(const Rect& rectangle) const
{
    Rect intersection;
    return intersects(rectangle, intersection);
}


////////////////////////////////////////////////////////////
bool Rect::intersects(const Rect& rectangle, Rect& intersection) const
{
    double left   = std::max(pos.x,          rectangle.pos.x),
           top    = std::max(pos.y,          rectangle.pos.y),
           right  = std::min(pos.x + size.x, rectangle.pos.x + rectangle.size.x),
           bottom = std::min(pos.y + size.y, rectangle.pos.y + rectangle.size.y);
    
    if( (left < right) && (top < bottom) )
    {
        intersection = Rect(Vector2d(left, top), Vector2d(right - left, bottom - top));
        return true;
    }
    
    else
    {
        intersection = Rect();
        return false;
    }
}

}