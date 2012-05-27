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

#include <Zoost/Transform.hpp>

namespace zin
{
    
////////////////////////////////////////////////////////////
Transform::Transform()
{
    init();
}

////////////////////////////////////////////////////////////
Transform::Transform(double value)
{
    for( auto& v : m_values )
        value = v;
}

////////////////////////////////////////////////////////////
Transform::Transform(const std::array<double, 9>& values) : 
m_values(values) {}

////////////////////////////////////////////////////////////   
void Transform::init()
{
    m_values[0] = 1;
    m_values[1] = 0;
    m_values[2] = 0;
    m_values[3] = 0;
    m_values[4] = 1;
    m_values[5] = 0;
    m_values[6] = 0;
    m_values[7] = 0;
    m_values[8] = 1;
}

////////////////////////////////////////////////////////////
Point Transform::operator*(const Vector2d& vector)
{
    return getMultiplication(vector);
}

////////////////////////////////////////////////////////////
Point Transform::getMultiplication(const Vector2d& vector)
{
    return Vector2d(m_values[0] * vector.x + m_values[1] * vector.y + m_values[2], m_values[3] * vector.x + m_values[4] * vector.y + m_values[5]);
}

////////////////////////////////////////////////////////////
Transform Transform::operator*(const Transform& transformation)
{
    return getMultiplication(transformation);
}

////////////////////////////////////////////////////////////
Transform Transform::getMultiplication(const Transform& transformation)
{
    Transform temp = *this;
    temp.multiply(transformation);
    
    return temp;
}

////////////////////////////////////////////////////////////
Transform& Transform::operator*=(const Transform& transformation)
{
    return multiply(transformation);
}

////////////////////////////////////////////////////////////
Transform& Transform::multiply(const Transform& transformation)
{
    std::array<double, 9> temp = m_values;
    
    m_values[0] = temp[0] * transformation[0] + temp[1] * transformation[3] + temp[2] * transformation[6];
    m_values[1] = temp[0] * transformation[1] + temp[1] * transformation[4] + temp[2] * transformation[7];
    m_values[2] = temp[0] * transformation[2] + temp[1] * transformation[5] + temp[2] * transformation[8];
    m_values[3] = temp[3] * transformation[0] + temp[4] * transformation[3] + temp[5] * transformation[6];
    m_values[4] = temp[3] * transformation[1] + temp[4] * transformation[4] + temp[5] * transformation[7];
    m_values[5] = temp[3] * transformation[2] + temp[4] * transformation[5] + temp[5] * transformation[8];
    m_values[6] = temp[6] * transformation[0] + temp[7] * transformation[3] + temp[8] * transformation[6];
    m_values[7] = temp[6] * transformation[1] + temp[7] * transformation[4] + temp[8] * transformation[7];
    m_values[8] = temp[6] * transformation[2] + temp[7] * transformation[5] + temp[8] * transformation[8];
            
    return *this;
}

////////////////////////////////////////////////////////////
Transform& Transform::operator=(const Transform& transformation)
{
    m_values = transformation.m_values;
    return *this;
}

////////////////////////////////////////////////////////////
bool Transform::operator==(const Transform& transformation) 
{
    return m_values == transformation.m_values;
}

////////////////////////////////////////////////////////////
bool Transform::operator!=(const Transform& transformation)
{
    return m_values != transformation.m_values;
}

////////////////////////////////////////////////////////////
double& Transform::operator[](Indice indice) const
{
    return m_values[indice];
}

////////////////////////////////////////////////////////////
Transform Transform::getInverse()
{
    Transform inverse;
    
    const double det = getDeterminant();
    
    inverse[0] =  (m_values[4] * m_values[8] - m_values[7] * m_values[5]) / det;
    inverse[1] = -(m_values[1] * m_values[8] - m_values[7] * m_values[2]) / det;
    inverse[2] =  (m_values[1] * m_values[5] - m_values[4] * m_values[2]) / det;
    inverse[3] = -(m_values[3] * m_values[8] - m_values[6] * m_values[5]) / det;
    inverse[4] =  (m_values[0] * m_values[8] - m_values[6] * m_values[2]) / det;
    inverse[5] = -(m_values[0] * m_values[5] - m_values[3] * m_values[2]) / det;
    inverse[6] =  (m_values[3] * m_values[7] - m_values[6] * m_values[4]) / det;
    inverse[7] = -(m_values[0] * m_values[7] - m_values[6] * m_values[1]) / det;
    inverse[8] =  (m_values[0] * m_values[4] - m_values[3] * m_values[1]) / det;
    
    return inverse;
}

////////////////////////////////////////////////////////////
double* Transform::getValues()
{
    double values[9] = {m_values[0], m_values[1], m_values[2], m_values[3], m_values[4], m_values[5], m_values[6], m_values[7], m_values[8]};
    return values;
}

////////////////////////////////////////////////////////////
double Transform::getDeterminant()
{
    return m_values[0] * (m_values[4] * m_values[8] - m_values[7] * m_values[5]) -
           m_values[1] * (m_values[3] * m_values[8] - m_values[6] * m_values[5]) +
           m_values[2] * (m_values[3] * m_values[8] - m_values[6] * m_values[5]);
}
    
////////////////////////////////////////////////////////////
Transform Transform::translation(double shiftX, double shiftY)
{
    Transform translation;
    
    translation[2] = shiftX;
    translation[5] = shiftY;
    
    return translation;
}

////////////////////////////////////////////////////////////
Transform Transform::translation(const Vector2d& shift)
{
    return translation(shift.x, shift.y);
}

////////////////////////////////////////////////////////////
Transform Transform::rotation(double angle, const Vector2d& origin)
{
    Transform rotation;
    
    rotation[0] =  std::cos(angle);
    rotation[1] = -std::sin(angle);
    rotation[3] =  std::sin(angle);
    rotation[4] =  std::cos(angle);
    
    if( origin != Vector2d(0, 0) )
        rotation = Transform::translation(origin) * rotation * Transform::translation(origin * -1);
    
    return rotation;
}

////////////////////////////////////////////////////////////
Transform Transform::scaling(double factorX, double factorY, const Vector2d& origin)
{
    Transform scaling;
    
    scaling[0] = factorX;
    scaling[4] = factorY;

    if( origin != Vector2d(0, 0) )
        scaling = Transform::translation(origin) * scaling * Transform::translation(origin * -1);
    
    return scaling;
}

////////////////////////////////////////////////////////////
Transform Transform::scaling(const Vector2d& factors, const Vector2d& origin)
{
    return scaling(factors.x, factors.y, origin);
}

////////////////////////////////////////////////////////////
Transform Transform::reflection(bool axisX, bool axisY)
{
    Transform inversion;
    
    if( axisX ) inversion[0] = -1.f;
    if( axisY ) inversion[4] = -1.f;
    
    return inversion;
}

////////////////////////////////////////////////////////////
Transform Transform::shearing(double factorX, double factorY)
{
    Transform shearing;
    
    shearing[1] = factorX;
    shearing[3] = factorY;
    
    return shearing;
}

////////////////////////////////////////////////////////////
Transform Transform::shearing(
    const Vector2d& factors
) {
    return shearing(factors.x, factors.y);
}

////////////////////////////////////////////////////////////
void Transform::translate(
    double shiftX,
    double shiftY
) {
    multiply(translation(shiftX, shiftY));
}

////////////////////////////////////////////////////////////
void Transform::translate(const Vector2d& shift)
{
    translate(shift.x, shift.y);
}

////////////////////////////////////////////////////////////
void Transform::rotate(double angle, const Vector2d& origin)
{
    multiply(Transform::rotation(angle, origin));
}

////////////////////////////////////////////////////////////
void Transform::scale(double factorX, double factorY, const Vector2d& origin)
{
    multiply(Transform::scaling(factorX, factorY, origin));
}

////////////////////////////////////////////////////////////
void Transform::scale( const Vector2d& factors, const Vector2d& origin)
{
    scale(factors.x, factors.y, origin);
}

////////////////////////////////////////////////////////////
void Transform::reflect(bool axisX, bool axisY)
{
    multiply(Transform::reflection(axisX, axisY));
}

////////////////////////////////////////////////////////////
void Transform::shear(double factorX, double factorY)
{
    multiply(Transform::shearing(factorX, factorY));
}

////////////////////////////////////////////////////////////
void Transform::shear(const Vector2d& factor)
{
    shear(factor.x, factor.y);
}

}