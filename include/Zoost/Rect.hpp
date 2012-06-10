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

#ifndef ZOOST_RECT_HPP
#define ZOOST_RECT_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <iostream>
#include <Zoost/Vector2.hpp>
#include <Zoost/Config.hpp>

namespace zin
{

class ZOOST_API Rect
{
public:

    ////////////////////////////////////////////////////////////
    // Default constructor
    ////////////////////////////////////////////////////////////
    Rect(const Point& pos = Point(0, 0), const Vector2d& size = Vector2d(0, 0));

    ////////////////////////////////////////////////////////////
    // Return true if the rect contains the point
    ////////////////////////////////////////////////////////////
    bool contains(const Point& point) const;
	
    ////////////////////////////////////////////////////////////
    // Return true if the rect intersects the given one
    ////////////////////////////////////////////////////////////
    bool intersects(const Rect& rectangle) const;
	
    ////////////////////////////////////////////////////////////
    // Return true if the rect intersects the given one
    ////////////////////////////////////////////////////////////
    bool intersects(const Rect& rectangle, Rect& intersection) const;
	
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    Point    pos;
    Vector2d size;
};

}

#endif // ZOOST_RECT_HPP
