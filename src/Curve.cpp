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
/////////////////////////////////////////////////////////////

#include <Zoost/Curve.hpp>
#include <Zoost/Math.hpp>
#include <Zoost/Segment.hpp>

namespace zin
{

////////////////////////////////////////////////////////////
Curve::Curve(const std::initializer_list<Point>& points) :
m_length(0)
{
	for( auto& point : points )
		addVertex(point);
}

////////////////////////////////////////////////////////////
Curve::Curve(const Curve& curve):
m_length(0)
{
    add(curve);
}

////////////////////////////////////////////////////////////
Curve& Curve::operator=(const Curve& curve)
{
    m_length = 0;
    Geom::operator=(curve);
    
    return *this;
}

////////////////////////////////////////////////////////////
Curve& Curve::add(const Curve& curve)
{
    size_t offset = getVerticesCount();

    for( auto& vertex : curve.m_vertices )
        addVertex(convertToLocal(curve.convertToGlobal(vertex->getCoords())));

    return *this;
}

////////////////////////////////////////////////////////////
Curve Curve::operator+(const Curve& curve)
{
    Curve copy = *this;
    return copy.add(curve);
}

////////////////////////////////////////////////////////////
Curve& Curve::operator+=(const Curve& curve)
{
    return add(curve);
}

////////////////////////////////////////////////////////////
Vertex& Curve::addVertex(const Point& point)
{
    Vertex& vertex = Geom::addVertex(point);

    if( getVerticesCount() > 1 )
        m_length+=Geom::addLiaison(getVertex(getVerticesCount() - 2), vertex).getSegment().length();

    return getVertex(getVerticesCount() - 1);
}

////////////////////////////////////////////////////////////
Coords Curve::operator[](double factor) const
{
    size_t size = getVerticesCount();

    if( size > 1 )
    {
        if( factor > 1 )
            factor = 1;

        else if( factor < 0 )
            factor = 0;
        
        double distPoint = m_length * factor, dist = 0;
        
        for( auto& liaison : m_liaisons )
        {
            Segment segment(liaison->v1.getCoords(), liaison->v2.getCoords());
            double length = segment.length();

            dist+=length;
            
            if( dist >= distPoint )
                return segment[1 - (dist - distPoint) / length];
        }
    }
    
    else return {0, 0};
}

////////////////////////////////////////////////////////////
double Curve::getLength() const
{
    return m_length;
}

////////////////////////////////////////////////////////////
Curve Curve::bezier(const std::initializer_list<Point>& keyPoints, Uint32 complexity)
{
	Curve curve;

    if( complexity < 2 )
		complexity = 2;

    std::vector<Point> keys = keyPoints;
        
    for( Uint32 k(0); k < complexity + 1; k++ )
    {
    	Point point;

    	for( size_t i(0); i < keyPoints.size(); i++ )
			point+=(keys[i] * Math::bernstein(i, keys.size() - 1, float(k) / float(complexity)));

		curve.addVertex(point);
    }

    return curve;
}

}