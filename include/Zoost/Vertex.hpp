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

#ifndef ZOOST_VERTEX_HPP
#define ZOOST_VERTEX_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <iostream>
#include <Zoost/Vector2.hpp>
#include <Zoost/Config.hpp>

namespace zin
{

class Geom;

struct ZOOST_API Vertex
{
    ////////////////////////////////////////////////////////////
    // Set the coords of the vertex
    ////////////////////////////////////////////////////////////   
    Vertex& operator=(const Coords& coords);

    ////////////////////////////////////////////////////////////
    // Set the coords of the vertex
    ////////////////////////////////////////////////////////////   
    void setCoords(const Coords& coords);

    ////////////////////////////////////////////////////////////
    // Get the coords of the vertex
    ////////////////////////////////////////////////////////////   
    const Coords& getCoords() const;

    ////////////////////////////////////////////////////////////
    // Get indice
    ////////////////////////////////////////////////////////////   
    size_t getIndice() const;

private:

    friend class Geom;

    ////////////////////////////////////////////////////////////
    // Default constructor
    ////////////////////////////////////////////////////////////
    Vertex(const Coords& coords, const Geom& geom);

    ////////////////////////////////////////////////////////////
    // Copy constructor
    /////////////////////////////////////////////////////////
    Vertex(const Vertex&);

    ////////////////////////////////////////////////////////////
    /// Assignment operator
    ////////////////////////////////////////////////////////////
    Vertex& operator=(const Vertex&);

    ////////////////////////////////////////////////////////////
    // Data member
    ////////////////////////////////////////////////////////////
    const Geom& m_geom;
    Coords      m_coords;
};

}

#endif // ZOOST_VERTEX_HPP