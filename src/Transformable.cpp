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

#include <Zoost/Transformable.hpp>

namespace zin
{

////////////////////////////////////////////////////////////
Transformable::Transformable(const Vector2d& position, double rotation, const Vector2d& scale) :
m_position(position),
m_rotation(rotation),
m_scale(scale),
m_transformUpdated(true),
m_invTransformUpdated(true) {}

////////////////////////////////////////////////////////////
Transformable& Transformable::operator=(const Transformable& transformable)
{
    m_transform           = transformable.m_transform;
    m_invTransform        = transformable.m_invTransform;
    m_transformUpdated    = transformable.m_transformUpdated;
    m_invTransformUpdated = transformable.m_invTransformUpdated;
    m_origin              = transformable.m_origin;
    m_position            = transformable.m_position;
    m_scale               = transformable.m_scale;
    m_rotation            = transformable.m_rotation;
}

////////////////////////////////////////////////////////////
void Transformable::init()
{
    m_transform.init();
    m_invTransform.init();

    m_transformUpdated    = true;
    m_invTransformUpdated = true;
    m_origin              = Point();
    m_position            = Coords();
    m_scale               = Vector2d(1, 1);
    m_rotation            = 0;
}

////////////////////////////////////////////////////////////
void Transformable::setPositionX(double posX)
{
    m_position.x = posX;
    
    m_transformUpdated    = false;
    m_invTransformUpdated = false;
}

////////////////////////////////////////////////////////////
void Transformable::setPositionY(double posY)
{
    m_position.y = posY;
    
    m_transformUpdated    = false;
    m_invTransformUpdated = false;
}

////////////////////////////////////////////////////////////
void Transformable::setPosition(double posX, double posY)
{
    setPositionX(posX);
    setPositionY(posY);
}

////////////////////////////////////////////////////////////
void Transformable::setPosition(const Point& pos)
{
    setPosition(pos.x, pos.y);
}

////////////////////////////////////////////////////////////
void Transformable::moveX(double shiftX)
{
    setPositionX(m_position.x + shiftX);
}

////////////////////////////////////////////////////////////
void Transformable::moveY(double shiftY)
{
    setPositionY(m_position.y + shiftY);
}

////////////////////////////////////////////////////////////
void Transformable::move(double shiftX, double shiftY)
{
    moveX(shiftX);
    moveY(shiftY);
}

////////////////////////////////////////////////////////////
void Transformable::move(
    const Vector2d& shift
) {
    move(shift.x, shift.y);
}

////////////////////////////////////////////////////////////
double Transformable::getPositionX()
{
    return m_position.x;
}

////////////////////////////////////////////////////////////
double Transformable::getPositionY()
{
    return m_position.y;
}

////////////////////////////////////////////////////////////
Point Transformable::getPosition()
{
    return m_position;
}

////////////////////////////////////////////////////////////
void Transformable::setRotation(double angle)
{
    m_rotation = angle;
    
    m_transformUpdated    = false;
    m_invTransformUpdated = false;
}

////////////////////////////////////////////////////////////
void Transformable::rotate(double angle)
{
    setRotation(m_rotation + angle);
}

////////////////////////////////////////////////////////////
double Transformable::getRotation()
{
    return m_rotation;
}

////////////////////////////////////////////////////////////
void Transformable::setScaleX(double factorX)
{
    if( factorX > 0 )
    {
        m_scale.x = factorX;
        
        m_transformUpdated    = false;
        m_invTransformUpdated = false;
    }
}

////////////////////////////////////////////////////////////
void Transformable::setScaleY(double factorY)
{
    if( factorY > 0 )
    {
        m_scale.y = factorY;
    
        m_transformUpdated    = false;
        m_invTransformUpdated = false;
    }
}

////////////////////////////////////////////////////////////
void Transformable::setScale(double factorX, double factorY)
{
    setScaleX(factorX);
    setScaleY(factorY);
}

////////////////////////////////////////////////////////////
void Transformable::setScale(const Vector2d& factors)
{
    setScale(factors.x, factors.y);
}

////////////////////////////////////////////////////////////
void Transformable::scaleX(double factorX)
{
    setScaleX(m_scale.x + factorX);
}

////////////////////////////////////////////////////////////
void Transformable::scaleY(double factorY)
{
    setScaleY(m_scale.y + factorY);
}

////////////////////////////////////////////////////////////
void Transformable::scale(double factorX, double factorY)
{
    scaleX(factorX);
    scaleY(factorY);
}

////////////////////////////////////////////////////////////
void Transformable::scale(const Vector2d& factors)
{
    scale(factors.x, factors.y);
}

////////////////////////////////////////////////////////////
Vector2d Transformable::getScale()
{
    return m_scale;
}

////////////////////////////////////////////////////////////
void Transformable::setOrigin(double x,double y) 
{
    m_origin.x = x;
    m_origin.y = y;

    m_transformUpdated    = false;
    m_invTransformUpdated = false;
}


////////////////////////////////////////////////////////////
void Transformable::setOrigin(const Vector2d& origin)
{
    setOrigin(origin.x, origin.y);
}

////////////////////////////////////////////////////////////
const Vector2d& Transformable::getOrigin() const
{
    return m_origin;
}

////////////////////////////////////////////////////////////
Point Transformable::convertToGlobal(const Point& point) const
{
    return getTransform() * point;
}

////////////////////////////////////////////////////////////
Point Transformable::convertToGlobal(const double pointX, const double pointY) const
{
    return convertToGlobal(Point(pointX, pointY));
}

////////////////////////////////////////////////////////////
Segment Transformable::convertToGlobal(const Segment& segment) const
{
    return Segment(convertToGlobal(segment.p1), convertToGlobal(segment.p2));
}

////////////////////////////////////////////////////////////
Point Transformable::convertToLocal(const Point& point) const
{
    return getInvTransform() * point;
}

////////////////////////////////////////////////////////////
Point Transformable::convertToLocal(const double pointX, const double pointY) const
{
    return convertToLocal(Point(pointX, pointY));
}

////////////////////////////////////////////////////////////
Segment Transformable::convertToLocal(const Segment& segment) const
{
    return Segment(convertToLocal(segment.p1), convertToLocal(segment.p2));
}

////////////////////////////////////////////////////////////
Transform& Transformable::getTransform() const
{
    if( !m_transformUpdated )
    {
        m_transform = Transform::translation(m_position) * Transform::rotation(m_rotation, m_origin) * Transform::scaling(m_scale, m_origin);
        m_transformUpdated = true;
    }
    
    return m_transform;
}

////////////////////////////////////////////////////////////
Transform& Transformable::getInvTransform() const
{
    if( !m_invTransformUpdated )
    {
        m_invTransform = getTransform().getInverse();
        m_invTransformUpdated = true;
    }
    
    return m_invTransform;
}

}