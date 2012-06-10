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

#include <Zoost/Math.hpp>

namespace zin
{

////////////////////////////////////////////////////////////
template <typename T>
Vector2<T>::Vector2(T X, T Y) :
x(X),
y(Y) {}

////////////////////////////////////////////////////////////
template <typename T>
Vector2<T>::Vector2(const Vector2<T>& vector) :
x(vector.x),
y(vector.y) {}

////////////////////////////////////////////////////////////
template <typename T>
void Vector2<T>::set(T X, T Y)
{
    x = X;
    y = Y;
}

////////////////////////////////////////////////////////////
template <typename T>
T Vector2<T>::length() const
{
    return std::sqrt(x*x + y*y);
}

////////////////////////////////////////////////////////////
template <typename T>
T Vector2<T>::length(const Vector2<T>& vector)
{
    return std::sqrt(vector.x*vector.x + vector.y*vector.y);
}
    
////////////////////////////////////////////////////////////
template <typename T>
T Vector2<T>::scalarProduct(const Vector2<T>& vector1, const Vector2<T>& vector2)
{
    return vector1.x * vector2.x + vector1.y * vector2.y;
}

////////////////////////////////////////////////////////////
template <typename T>
T Vector2<T>::angle(const Vector2<T>& A, const Vector2<T>& B)
{
    T angle = static_cast<T>(std::atan2(B.y, B.x) - std::atan2(A.y, A.x));

    if( angle > 3.14159265 )
        while( angle > 3.14159265 )
            angle-=(2*3.14159265);

    else if( angle < -3.14159265 )
        while( angle < -3.14159265 )
            angle+=(2*3.14159265);

    return static_cast<T>(angle * 180.f / 3.141592654f);
}

////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> Vector2<T>::getNormal()
{
    return Vector2<T>(x, y).normalize();
}

////////////////////////////////////////////////////////////
template <typename T>
void Vector2<T>::normalize()
{
    float lgth = length();

    if( lgth != 0 )
    {
        x/=lgth;
        y/=lgth;
    }
}

////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> Vector2<T>::operator+(const Vector2<T>& vector) const
{
    return Vector2<T>(x + vector.x, y + vector.y);
}
    
////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> Vector2<T>::operator-(const Vector2<T>& vector) const
{
    return Vector2<T>(x - vector.x, y - vector.y);
}

////////////////////////////////////////////////////////////
template <typename T>
Vector2<T>& Vector2<T>::operator*(const Vector2<T>& vector)
{
    return scalarProduct(*this, vector);
}

////////////////////////////////////////////////////////////
template <typename T>
Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& vector)
{
    x+=vector.x;
    y+=vector.y;
    
    return *this;
}

////////////////////////////////////////////////////////////
template <typename T>
Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& vector)
{
    x-=vector.x;
    y-=vector.y;
    
    return *this;
}

////////////////////////////////////////////////////////////
template <typename T>
bool Vector2<T>::operator==(const Vector2<T>& vector) const
{
    return x == vector.x && y == vector.y;
}
                
////////////////////////////////////////////////////////////
template <typename T>
bool Vector2<T>::operator!=(const Vector2<T>& vector) const
{
    return x != vector.x || y != vector.y;
}

////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> Vector2<T>::operator+(T value) const
{
    return Vector2<T>(x + value, y + value);
}
    
////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> Vector2<T>::operator-(T value) const
{
    return Vector2<T>(x - value, y - value);
}

////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> Vector2<T>::operator*(T value) const
{
    return Vector2<T>(x * value, y * value);
}
    
////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> Vector2<T>::operator/(T value) const
{
    return Vector2<T>(x / value, y / value);
}

////////////////////////////////////////////////////////////
template <typename T>
Vector2<T>& Vector2<T>::operator+=(T value)
{
    x+=value;
    y+=value;
    
    return *this;
}

////////////////////////////////////////////////////////////
template <typename T>
Vector2<T>& Vector2<T>::operator-=(T value)
{
    x-=value;
    y-=value;
    
    return *this;
}

////////////////////////////////////////////////////////////
template <typename T>
Vector2<T>& Vector2<T>::operator*=(T value)
{
    x*=value;
    y*=value;
    
    return *this;
}
    
////////////////////////////////////////////////////////////
template <typename T>
Vector2<T>& Vector2<T>::operator/=(T value)
{
    if( value != 0 )
    {
        x/=value;
        y/=value;
    }
    
    return *this;
}

}