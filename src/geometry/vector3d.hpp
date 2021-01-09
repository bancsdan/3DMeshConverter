#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

class Vector3d {
    double m_x;
    double m_y;
    double m_z;
public:
    Vector3d() = default;
    Vector3d(double x, double y, double z);

    double GetLength() const noexcept;
    double DotProduct(const Vector3d& other) const noexcept;

    friend Vector3d operator-(const Vector3d& lhs, const Vector3d& rhs) noexcept;
    friend Vector3d operator+(const Vector3d& lhs, const Vector3d& rhs) noexcept;
    friend Vector3d operator*(const Vector3d& lhs, double scale) noexcept;
    friend Vector3d operator/(const Vector3d& lhs, double scale) noexcept;
};

#endif