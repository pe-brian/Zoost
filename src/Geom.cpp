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

#include <Zoost/Geom.hpp>

namespace zin
{

////////////////////////////////////////////////////////////
Geom::Geom() :
m_rectUpdated(false) {}

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
void Geom::notify(size_t notification, size_t id) const
{
    for( auto& observer : m_observers )
        observer->onNotification(notification, id);
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
    
    m_rectUpdated = false;

    notify(CLEAR);
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

    m_rectUpdated = false;

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

    m_rectUpdated = false;//getBounds().contains(convertToGlobal(coords));

    notify(CREATED_VERTEX, m_vertices.size() - 1);
    
    return *vertex;
}

////////////////////////////////////////////////////////////
Liaison& Geom::addLiaison(const Vertex& vertex1, const Vertex& vertex2)
{
    Liaison* liaison = new Liaison(vertex1, vertex2, *this);
    m_liaisons.push_back(liaison);

    notify(CREATED_LIAISON, m_liaisons.size() - 1);
    
    return *liaison;
}

////////////////////////////////////////////////////////////
Face& Geom::addFace(const Vertex& vertex1, const Vertex& vertex2, const Vertex& vertex3)
{
    Face* face = new Face(vertex1, vertex2, vertex3, *this);
    m_faces.push_back(face);

    notify(CREATED_FACE, m_faces.size() - 1);
    
    return *face;
}

////////////////////////////////////////////////////////////
void Geom::removeVertex(const Vertex& vertex)
{

}

////////////////////////////////////////////////////////////
void Geom::removeLiaison(const Liaison& liaison)
{
    for( auto it = m_liaisons.begin(); it != m_liaisons.end(); ++it )
        if( *it == &liaison )
        {
            delete *it;
            m_liaisons.erase(it);
            break;
        }
}

////////////////////////////////////////////////////////////
void Geom::removeFace(const Face& face)
{
    for( auto it = m_faces.begin(); it != m_faces.end(); ++it )
        if( *it == &face )
        {
            delete *it;
            m_faces.erase(it);
            break;
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
    if( getBounds().intersects(geom.getBounds()) )
        
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
    if( getBounds().intersects(geom.getBounds()) )

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
bool Geom::contains(const Point& point)
{
    if( getBounds().contains(point) )

        for( auto& face : m_faces )
        {
            Triangle triangle = face->getTriangle();

            if( triangle.contains(point) )
                return true;
        }
	
	return false;
}

////////////////////////////////////////////////////////////
bool Geom::contains(const Point& point, std::vector<Face*>& faces)
{
    if( getBounds().contains(point) )

        for( auto& face : m_faces )
        {
            Triangle triangle = face->getTriangle();

            if( triangle.contains(point) )
                faces.push_back(face);
        }
	
	return !faces.empty();
}

////////////////////////////////////////////////////////////
void Geom::computeBounds() const
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
        
    m_rect.pos  = min;
    m_rect.size = max - min;

    if( m_rect.size.x == 0 ) m_rect.size.x = 1;
    if( m_rect.size.y == 0 ) m_rect.size.y = 1;
        
    m_rectUpdated = true;
}

////////////////////////////////////////////////////////////
const Rect& Geom::getBounds() const
{
    if( !m_rectUpdated || !m_transformUpdated )
	    computeBounds();
	
	return m_rect;
}

////////////////////////////////////////////////////////////
Geom Geom::segment(const Coords& coords1, const Coords& coords2, const Coords& position, double rotation)
{
    Geom geom;

    geom.setPosition(position);
    geom.setRotation(rotation);

    Vertex& vertex1 = geom.addVertex(coords1);
    Vertex& vertex2 = geom.addVertex(coords2);

    geom.addLiaison(vertex1, vertex2);

    return geom;
}

////////////////////////////////////////////////////////////
Geom Geom::triangle(const Coords& coords1, const Coords& coords2, const Coords& coords3, const Coords& position, double rotation)
{
    Geom geom;

    geom.setPosition(position);
    geom.setRotation(rotation);

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
Geom Geom::quad(const Coords& coords1, const Coords& coords2, const Coords& coords3, const Coords& coords4, const Coords& position, double rotation)
{
    Geom geom;

    geom.setPosition(position);
    geom.setRotation(rotation);

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
Geom Geom::rectangle(const Coords& size, const Coords& position, double rotation)
{
    return quad(Coords{0, 0}, Coords{size.x, 0}, Coords{size.x, size.y}, Coords{0, size.y}, position, rotation);
}

////////////////////////////////////////////////////////////
Geom Geom::rectangle(const Rect& rect, double rotation)
{
    return rectangle(rect.pos, rect.size, rotation);
}

////////////////////////////////////////////////////////////
Geom Geom::scare(double length, const Coords& position, double rotation)
{
    return rectangle(Coords(length, length), position, rotation);
}

////////////////////////////////////////////////////////////
Geom Geom::circle(double radius, const Coords& position, double rotation)
{
    return polygon(radius, 40, position, rotation);
}
    
////////////////////////////////////////////////////////////
Geom Geom::star(const Coords& position, double rotation, double width1, double width2, unsigned int complexity)
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

    geom.setPosition(position);
    geom.setRotation(rotation);
    
    return geom;
}
    
////////////////////////////////////////////////////////////
Geom Geom::polygon(double width, unsigned int complexity, const Coords& position, double rotation)
{
    Geom geom;
    
    if( complexity < 5 )
        complexity = 5;

    double delta = 6.28318531 / double(complexity), angus = -1.57079633;

    Vertex& vertex = geom.addVertex({0, 0});
        
    for( size_t k(0); k < complexity; k+=2 )
    {
        Vertex& vertex1 = geom.addVertex({std::cos(angus        ) * width, std::sin(angus        ) * width});
        Vertex& vertex2 = geom.addVertex({std::cos(angus + delta) * width, std::sin(angus + delta) * width});

        geom.addLiaison(vertex1, vertex2);
        geom.addFace(vertex, vertex1, vertex2);

        angus+=delta;
    }

    geom.setPosition(position);
    geom.setRotation(rotation);
    
    return geom;
}

////////////////////////////////////////////////////////////
Geom Geom::polygon(const std::initializer_list<Point>& points, const Coords& position, double rotation)
{
    Geom geom;

    geom.setPosition(position);
    geom.setRotation(rotation); 

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