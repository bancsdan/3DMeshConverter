#include <math.h>

#include "vector3d.hpp"

Vector3d::Vector3d(double x, double y, double z) : m_x(x), m_y(y), m_z(z)
{
}

double Vector3d::GetLength() const noexcept
{
    return sqrt(pow(m_x, 2) + pow(m_y, 2) + pow(m_z, 2));
}

Vector3d operator-(const Vector3d& lhs, const Vector3d& rhs) noexcept
{
    return {lhs.m_x - rhs.m_x, lhs.m_y - rhs.m_y, lhs.m_z - rhs.m_z};
}

 Vector3d operator+(const Vector3d&  lhs, const Vector3d&  rhs) noexcept
 {
    return {lhs.m_x + rhs.m_x, lhs.m_y + rhs.m_y, lhs.m_z + rhs.m_z};
 }

Vector3d operator*(const Vector3d&  lhs, double  scale) noexcept
{
    return {lhs.m_x * scale, lhs.m_y * scale, lhs.m_z * scale};
}

Vector3d operator/(const Vector3d&  lhs, double  scale) noexcept
{
    return {lhs.m_x / scale, lhs.m_y / scale, lhs.m_z / scale};
}