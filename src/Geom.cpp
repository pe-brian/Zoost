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

#include <Zoost/Geom.hpp>
#include <Zoost/Converter.hpp>

namespace zin
{

////////////////////////////////////////////////////////////
Geom::Geom() {}

////////////////////////////////////////////////////////////
Geom::Geom(const Geom& geom) :
Transformable(geom)
{
    clear();
    add(geom);
}

////////////////////////////////////////////////////////////
Geom& Geom::operator=(const Geom& geom)
{
    Transformable::operator=(geom);
    
    clear();
    add(geom);
    
    return *this;
}

////////////////////////////////////////////////////////////
Geom::~Geom()
{
    clear();
}

////////////////////////////////////////////////////////////
void Geom::addObserver(Observer& observer)
{
    m_observers.insert(&observer);
}

////////////////////////////////////////////////////////////
void Geom::removeObserver(Observer& observer)
{
    m_observers.erase(&observer);
}

////////////////////////////////////////////////////////////
void Geom::clear()
{
    for( auto& vertex : m_vertices )
        delete vertex;

    m_vertices.clear();

    for( auto& liaison : m_liaisons )
        delete liaison;

    m_liaisons.clear();

    for( auto& face : m_faces )
        delete face;

    m_faces.clear();

    for( auto& observer : m_observers )
        observer->onErasing();

    m_localBoundsUpdated = false;
}

////////////////////////////////////////////////////////////
Geom& Geom::add(const Geom& geom)
{
    size_t offset = getVerticesCount();

    for( auto& vertex : geom.m_vertices )
        addVertex(convertToLocal(geom.convertToGlobal(vertex->getCoords())));
    
    for( auto& liaison : geom.m_liaisons )
        addLiaison(getVertex(liaison->v1.getIndice() + offset), getVertex(liaison->v2.getIndice() + offset));

    for( auto& face : geom.m_faces )
        addFace(getVertex(face->v1.getIndice() + offset), getVertex(face->v2.getIndice() + offset), getVertex(face->v3.getIndice() + offset));

    m_localBoundsUpdated = false;
    m_globalBoundsUpdated = false;

    for( auto& observer : geom.m_observers )
        m_observers.insert(observer);

    return *this;
}

////////////////////////////////////////////////////////////
Geom Geom::operator+(const Geom& geom)
{
    Geom copy = *this;
    return copy.add(geom);
}

////////////////////////////////////////////////////////////
Geom& Geom::operator+=(const Geom& geom)
{
    return add(geom);
}

////////////////////////////////////////////////////////////
Vertex& Geom::addVertex(const Coords& coords)
{
    Vertex* vertex = new Vertex(coords, *this);
    m_vertices.push_back(vertex);

    m_localBoundsUpdated = false;
    m_globalBoundsUpdated = false;

    for( auto& observer : m_observers )
        observer->onVertexAdded();
    
    return *vertex;
}

////////////////////////////////////////////////////////////
Liaison& Geom::addLiaison(const Vertex& vertex1, const Vertex& vertex2)
{
    Liaison* liaison = new Liaison(vertex1, vertex2, *this);
    m_liaisons.push_back(liaison);

    for( auto& observer : m_observers )
        observer->onLiaisonAdded();
    
    return *liaison;
}

////////////////////////////////////////////////////////////
Face& Geom::addFace(const Vertex& vertex1, const Vertex& vertex2, const Vertex& vertex3)
{
    Face* face = new Face(vertex1, vertex2, vertex3, *this);
    m_faces.push_back(face);

    for( auto& observer : m_observers )
        observer->onFaceAdded();
    
    return *face;
}

////////////////////////////////////////////////////////////
void Geom::removeVertex(const Vertex& vertex)
{
    for( size_t k(0); k < m_liaisons.size(); )
    {
        if( &(m_liaisons[k]->v1) == &vertex || &(m_liaisons[k]->v2) == &vertex )
        {
            delete m_liaisons[k];
            m_liaisons.erase(m_liaisons.begin() + k);

            for( auto& observer : m_observers )
                observer->onLiaisonRemoved(k);
        }

        else k++;
    }

    for( size_t k(0); k < m_faces.size(); k++ )
    {
        if( &(m_faces[k]->v1) == &vertex || &(m_faces[k]->v2) == &vertex || &(m_faces[k]->v3) == &vertex )
        {
            delete m_faces[k];
            m_faces.erase(m_faces.begin() + k);

            for( auto& observer : m_observers )
                observer->onFaceRemoved(k);
        }

        else k++;
    }

    for( auto& observer : m_observers )
        observer->onVertexRemoved(vertex.getIndice());
}

////////////////////////////////////////////////////////////
void Geom::removeLiaison(const Liaison& liaison)
{
    size_t k = 0;

    for( auto it = m_liaisons.begin(); it != m_liaisons.end(); ++it )
    {
        if( *it == &liaison )
        {
            delete *it;
            m_liaisons.erase(it);

            for( auto& observer : m_observers )
                observer->onLiaisonRemoved(k);

            break;
        }

        k++;
    }
}

////////////////////////////////////////////////////////////
void Geom::removeFace(const Face& face)
{
    size_t k = 0;

    for( auto it = m_faces.begin(); it != m_faces.end(); ++it )
    {
        if( *it == &face )
        {
            delete *it;
            m_faces.erase(it);

            for( auto& observer : m_observers )
                observer->onLiaisonRemoved(k);

            break;
        }

        k++;
    }
}

////////////////////////////////////////////////////////////
Vertex& Geom::getVertex(size_t indice) const
{
    return *m_vertices[indice];
}

////////////////////////////////////////////////////////////
Liaison& Geom::getLiaison(size_t indice) const
{
    return *m_liaisons[indice];
}

////////////////////////////////////////////////////////////
Face& Geom::getFace(size_t indice) const
{
    return *m_faces[indice];
}

////////////////////////////////////////////////////////////
size_t Geom::getVerticesCount() const
{
    return m_vertices.size();
}

////////////////////////////////////////////////////////////
size_t Geom::getLiaisonsCount() const
{
    return m_liaisons.size();
}
////////////////////////////////////////////////////////////
size_t Geom::getFacesCount() const
{
    return m_faces.size();
}

////////////////////////////////////////////////////////////
bool Geom::intersects(const Geom& geom) const
{
    if( getGlobalBounds().intersects(geom.getGlobalBounds()) )
        
	    for( auto& liaison1 : m_liaisons )
	    {
	        Segment segment1 = liaison1->getSegment();
	        
            for( auto& liaison2 : geom.m_liaisons )
            {
                Segment segment2 = liaison2->getSegment();
                
                if( segment1.intersects(segment2) )
                    return true;
            }
        }
   
    return false;
}

////////////////////////////////////////////////////////////
bool Geom::intersects(const Geom& geom, std::vector<Intersection>& intersections)
{
    if( getGlobalBounds().intersects(geom.getGlobalBounds()) )

	    for( auto& liaison1 : m_liaisons )
        {
	        Segment segment1 = liaison1->getSegment();
	        
            for( auto& liaison2 : geom.m_liaisons )
            {
                Segment segment2 = liaison2->getSegment();
                
                Point result;
                
                if( segment1.intersects(segment2, result) )
                    intersections.push_back(Intersection{convertToGlobal(result), liaison1, liaison2});
            }
        }
	                         
	return !intersections.empty();
}

////////////////////////////////////////////////////////////
bool Geom::contains(Point point)
{
    point = convertToLocal(point);

    if( getLocalBounds().contains(point) )

        for( auto& face : m_faces )

            if( Triangle::contains(face->v1.getCoords(), face->v2.getCoords(), face->v3.getCoords(), point) )
                return true;
	
	return false;
}

////////////////////////////////////////////////////////////
bool Geom::contains(Point point, std::vector<Face*>& faces)
{
    point = convertToLocal(point);

    if( getLocalBounds().contains(point) )

        for( auto& face : m_faces )
        
            if( Triangle::contains(face->v1.getCoords(), face->v2.getCoords(), face->v3.getCoords(), point) )
                faces.push_back(face);
	
	return !faces.empty();
}

////////////////////////////////////////////////////////////
void Geom::computeLocalBounds() const
{
    Coords min, max;
    bool init = true;
        
    for( auto& vertex : m_vertices )
    {
         Coords coords = vertex->getCoords();
            
        if( init )
        {
            min = coords;
            max = coords;

            init = false;
        }
            
        else
        {
            min = Coords(std::min(coords.x, min.x), std::min(coords.y, min.y));
            max = Coords(std::max(coords.x, max.x), std::max(coords.y, max.y));
        }
    }
        
    m_localBounds.pos  = min;
    m_localBounds.size = max - min;

    if( m_localBounds.size.x == 0 )
        m_localBounds.size.x = 1;

    if( m_localBounds.size.y == 0 )
        m_localBounds.size.y = 1;
}

////////////////////////////////////////////////////////////
void Geom::computeGlobalBounds() const
{
    Coords min, max;
    bool init = true;
        
    for( auto& vertex : m_vertices )
    {
         Coords coords = convertToGlobal(vertex->getCoords());
            
        if( init )
        {
            min = coords;
            max = coords;

            init = false;
        }
            
        else
        {
            min = Coords(std::min(coords.x, min.x), std::min(coords.y, min.y));
            max = Coords(std::max(coords.x, max.x), std::max(coords.y, max.y));
        }
    }
        
    m_globalBounds.pos  = min;
    m_globalBounds.size = max - min;

    if( m_globalBounds.size.x == 0 )
        m_globalBounds.size.x = 1;

    if( m_globalBounds.size.y == 0 )
        m_globalBounds.size.y = 1;
}

////////////////////////////////////////////////////////////
Rect Geom::getLocalBounds() const
{
    if( !m_localBoundsUpdated )
    {
        computeLocalBounds();
        m_localBoundsUpdated = true;
    }

    return m_localBounds;
}

////////////////////////////////////////////////////////////
Rect Geom::getGlobalBounds() const
{
    if( !m_globalBoundsUpdated )
    {
        computeGlobalBounds();
        m_globalBoundsUpdated = true;
    }

    return m_globalBounds;
}

////////////////////////////////////////////////////////////
void Geom::onTransformUpdated() const
{
    m_globalBoundsUpdated = false;

    for( auto& observer : m_observers )
        observer->onTransformUpdated();
}

////////////////////////////////////////////////////////////
void Geom::onVertexMoved() const
{
    m_localBoundsUpdated = false;
    m_globalBoundsUpdated = false;

    for( auto& observer : m_observers )
        observer->onVertexMoved();
}

////////////////////////////////////////////////////////////
Geom Geom::segment(const Coords& coords1, const Coords& coords2)
{
    Geom geom;

    Vertex& vertex1 = geom.addVertex(coords1);
    Vertex& vertex2 = geom.addVertex(coords2);

    geom.addLiaison(vertex1, vertex2);

    return geom;
}

////////////////////////////////////////////////////////////
Geom Geom::triangle(const Coords& coords1, const Coords& coords2, const Coords& coords3)
{
    Geom geom;

    Vertex& vertex1 = geom.addVertex(coords1);
    Vertex& vertex2 = geom.addVertex(coords2);
    Vertex& vertex3 = geom.addVertex(coords3);

    geom.addLiaison(vertex1, vertex2);
    geom.addLiaison(vertex2, vertex3);
    geom.addLiaison(vertex3, vertex1);

    geom.addFace(vertex1, vertex2, vertex3);

    return geom;
}
    
////////////////////////////////////////////////////////////
Geom Geom::quad(const Coords& coords1, const Coords& coords2, const Coords& coords3, const Coords& coords4)
{
    Geom geom;

    Vertex& vertex1 = geom.addVertex(coords1);
    Vertex& vertex2 = geom.addVertex(coords2);
    Vertex& vertex3 = geom.addVertex(coords3);
    Vertex& vertex4 = geom.addVertex(coords4);

    geom.addLiaison(vertex1, vertex2);
    geom.addLiaison(vertex2, vertex3);
    geom.addLiaison(vertex3, vertex4);
    geom.addLiaison(vertex4, vertex1);

    geom.addFace(vertex1, vertex2, vertex3);
    geom.addFace(vertex3, vertex4, vertex1);

    return geom;
}

////////////////////////////////////////////////////////////
Geom Geom::rectangle(const Coords& size)
{
    return quad(Coords{0, 0}, Coords{size.x, 0}, Coords{size.x, size.y}, Coords{0, size.y});
}

////////////////////////////////////////////////////////////
Geom Geom::rectangle(const Rect& rect)
{
    Geom geom = rectangle(rect.size);
    geom.setPosition(rect.pos);

    return geom;
}

////////////////////////////////////////////////////////////
Geom Geom::rectangle(const Point& point1, const Point& point2, unsigned int width)
{
    double angle = std::atan((point2.y - point1.y) / (point2.x - point1.x));

    Point p1(point1.x + width * std::cos(angle + toRads( 90)), point1.y + width * std::sin(angle + toRads( 90)));
    Point p2(point1.x + width * std::cos(angle + toRads(270)), point1.y + width * std::sin(angle + toRads(270)));
    Point p3(point2.x + width * std::cos(angle + toRads(270)), point2.y + width * std::sin(angle + toRads(270)));
    Point p4(point2.x + width * std::cos(angle + toRads( 90)), point2.y + width * std::sin(angle + toRads( 90)));

    return quad(p1, p2, p3, p4);
}

////////////////////////////////////////////////////////////
Geom Geom::scare(double length)
{
    return rectangle(Coords(length, length));
}

////////////////////////////////////////////////////////////
Geom Geom::circle(double radius)
{
    return polygon(radius, 40);
}
    
////////////////////////////////////////////////////////////
Geom Geom::star(double width1, double width2, unsigned int complexity)
{
    Geom geom;
    
    if( complexity < 3 )
        complexity = 3;

    double delta = 6.28318531 / double(complexity), angus = -1.57079633;

    Vertex& vertex = geom.addVertex({0, 0});
                
    for( size_t k(1); k <= 2*complexity + 1; k++ )
    {
        Vertex& vertex1 = geom.addVertex({std::cos(angus          ) * width1, std::sin(angus          ) * width1});
        Vertex& vertex2 = geom.addVertex({std::cos(angus + delta/2) * width2, std::sin(angus + delta/2) * width2});

        if( k >= 3 )
        {
            geom.addLiaison(geom.getVertex(geom.getVerticesCount() - 3), vertex1);
            geom.addFace(geom.getVertex(0), geom.getVertex(geom.getVerticesCount() - 3), vertex1);
        }

        geom.addLiaison(vertex1, vertex2);
        geom.addFace(geom.getVertex(0), vertex1, vertex2);

        angus+=delta;
    }
    
    return geom;
}
    
////////////////////////////////////////////////////////////
Geom Geom::polygon(double width, unsigned int complexity)
{
    Geom geom;
    
    if( complexity < 5 )
        complexity = 5;

    double delta = 6.28318531f / double(complexity), angus = -1.57079633f;

    Vertex& vertex = geom.addVertex({0, 0});
        
    for( size_t k(0); k < complexity; k+=2 )
    {
        Vertex& vertex1 = geom.addVertex({std::cos(angus        ) * width, std::sin(angus        ) * width});
        Vertex& vertex2 = geom.addVertex({std::cos(angus + delta) * width, std::sin(angus + delta) * width});

        geom.addLiaison(vertex1, vertex2);
        geom.addFace(vertex, vertex1, vertex2);

        angus+=delta;
    }
    
    return geom;
}

////////////////////////////////////////////////////////////
Geom Geom::polygon(const std::initializer_list<Point>& points)
{
    Geom geom;

    if( points.size() > 3 )
    {
        for( auto& pts : points )
            geom.addVertex(pts);

        size_t size = geom.getVerticesCount();

        std::vector<size_t> index;

        for( size_t k(0); k < size; k++ )
        {
            index.push_back(k);

            if( k < size - 1 )
                geom.addLiaison(geom.getVertex(k), geom.getVertex(k + 1));

            else geom.addLiaison(geom.getVertex(k), geom.getVertex(0));
        }

        double sum = 0;

        for( size_t k(0); k < size; k++ )
        {
            Coords p1 = geom.getVertex(index[k]).getCoords(), p2 = geom.getVertex(index[(k + 1) % size]).getCoords();
            sum+=(p1.x*p2.y - p2.x*p1.y);
        }

        double orientation = sum / Math::abs(sum);

        while( size > 1 )

            for( size_t i(0); i < size; i++ )
            {
                size_t a = i == 0 ? size - 1 : i - 1, b = i, c = (i + 1) % size;

                Coords A = geom.getVertex(index[a]).getCoords(),
                       B = geom.getVertex(index[b]).getCoords(),
                       C = geom.getVertex(index[c]).getCoords();

                if( Vector2d::angle(Coords(B - A), Coords(C - B)) * orientation >= 0 )
                {
                    bool earFound = true;

                    for( size_t k(0); k < size; k++ )
                    {
                        Coords P = geom.getVertex(index[k]).getCoords();

                        if( A != P && B != P && C != P )
                        
                            if( Triangle::contains(A, B, C, P) )
                            {
                                earFound = false;
                                break;
                            }
                    }

                    if( earFound )
                    {
                        geom.addFace(geom.getVertex(index[a]), geom.getVertex(index[b]), geom.getVertex(index[c]));
                        index.erase(index.begin() + i);
                        size = index.size();

                        break;
                    }
                }
            }
    }

    else
    {
        std::vector<Coords> pts = points;

        if( pts.size() == 3 )
            geom = triangle(pts[0], pts[1], pts[2]);

        else if( pts.size() == 2 )
            geom = segment(pts[0], pts[1]);

        return geom;
    }
}

}