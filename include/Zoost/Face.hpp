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

#ifndef ZOOST_FACE_HPP
#define ZOOST_FACE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Zoost/Vertex.hpp>
#include <Zoost/Triangle.hpp>
#include <Zoost/Config.hpp>

namespace zin
{

class Geom;

struct ZOOST_API Face
{
    ////////////////////////////////////////////////////////////
    // Get the triangle matching to the face
    ////////////////////////////////////////////////////////////
    Triangle getTriangle();

    ////////////////////////////////////////////////////////////
    // Data member
    ////////////////////////////////////////////////////////////
    const Vertex& v1;
    const Vertex& v2;
    const Vertex& v3;

private:

    friend class Geom;

    ////////////////////////////////////////////////////////////
    // Default constructor
    ////////////////////////////////////////////////////////////
    Face(const Vertex& vertex1, const Vertex& vertex2, const Vertex& vertex3, const Geom& geom);

    ////////////////////////////////////////////////////////////
    // Copy constructor
    /////////////////////////////////////////////////////////
    Face(const Face&);

    ////////////////////////////////////////////////////////////
    /// Assignment operator
    ////////////////////////////////////////////////////////////
    Face& operator=(const Face&);

    ////////////////////////////////////////////////////////////
    // Data member
    ////////////////////////////////////////////////////////////
    const Geom& m_geom;
};

}

#endif // ZOOST_FACE_HPP