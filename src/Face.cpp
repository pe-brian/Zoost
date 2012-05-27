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

#include <Zoost/Face.hpp>
#include <Zoost/Geom.hpp>

namespace zin
{

////////////////////////////////////////////////////////////
Face::Face(const Vertex& vertex1, const Vertex& vertex2, const Vertex& vertex3, const Geom& geom) :
v1(vertex1),
v2(vertex2),
v3(vertex3),
m_geom(geom) {}

////////////////////////////////////////////////////////////
Triangle Face::getTriangle()
{
    return Triangle(m_geom.convertToGlobal(v1.getCoords()), m_geom.convertToGlobal(v2.getCoords()), m_geom.convertToGlobal(v3.getCoords()));
}

}