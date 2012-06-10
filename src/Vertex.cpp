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

#include <Zoost/Vertex.hpp>
#include <Zoost/Geom.hpp>

namespace zin
{

////////////////////////////////////////////////////////////   
Vertex& Vertex::operator=(const Coords& coords)
{
    setCoords(coords);
}

////////////////////////////////////////////////////////////   
void Vertex::setCoords(const Coords& coords)
{
    m_coords = coords;
    m_geom.onVertexMoved();
}

////////////////////////////////////////////////////////////   
const Coords& Vertex::getCoords() const
{
    return m_coords;
}

////////////////////////////////////////////////////////////   
size_t Vertex::getIndice() const
{
    size_t k = 0;

    for( ; k < m_geom.getVerticesCount(); k++ )
        if( this == &m_geom.getVertex(k) )
            break;

    return k;
}

////////////////////////////////////////////////////////////
Vertex::Vertex(const Coords& coords, const Geom& geom) :
m_coords(coords),
m_geom(geom) {}

}