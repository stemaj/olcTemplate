#ifndef __QUATERNION_HPP
#define __QUATERNION_HPP

#include <iostream>
#include <cmath>

namespace stemaj {

template <typename T>
class Quaternion {
public:
    T w, x, y, z;

    // Konstruktoren
    Quaternion() : w(1), x(0), y(0), z(0) {}
    Quaternion(T w, T x, T y, T z) : w(w), x(x), y(y), z(z) {}

    // Norm der Quaternion
    T norm() const {
        return std::sqrt(w * w + x * x + y * y + z * z);
    }

    // Konjugation der Quaternion
    Quaternion conjugate() const {
        return Quaternion(w, -x, -y, -z);
    }

    // Invertierung der Quaternion
    Quaternion inverse() const {
        T n = norm();
        if (n == 0) throw std::runtime_error("Inverse einer Null-Quaternion ist nicht definiert");
        return conjugate() / (n * n);
    }

    // Addition von zwei Quaternions
    Quaternion operator+(const Quaternion& q) const {
        return Quaternion(w + q.w, x + q.x, y + q.y, z + q.z);
    }

    // Subtraktion von zwei Quaternions
    Quaternion operator-(const Quaternion& q) const {
        return Quaternion(w - q.w, x - q.x, y - q.y, z - q.z);
    }

    // Skalare Multiplikation
    Quaternion operator*(T scalar) const {
        return Quaternion(w * scalar, x * scalar, y * scalar, z * scalar);
    }

    // Quaternion-Multiplikation
    Quaternion operator*(const Quaternion& q) const {
        return Quaternion(
            w * q.w - x * q.x - y * q.y - z * q.z,
            w * q.x + x * q.w + y * q.z - z * q.y,
            w * q.y - x * q.z + y * q.w + z * q.x,
            w * q.z + x * q.y - y * q.x + z * q.w
        );
    }

    // Skalare Division
    Quaternion operator/(T scalar) const {
        if (scalar == 0) throw std::runtime_error("Division durch Null");
        return Quaternion(w / scalar, x / scalar, y / scalar, z / scalar);
    }

    // Ausgabeoperator überladen
    friend std::ostream& operator<<(std::ostream& os, const Quaternion& q) {
        os << "(" << q.w << ", " << q.x << ", " << q.y << ", " << q.z << ")";
        return os;
    }
    
    // Rotiert einen Vektor (x, y, z) mit der Quaternion
    std::array<T, 3> rotate(const std::array<T, 3>& v) const {
        Quaternion qv(0, v[0], v[1], v[2]);
        Quaternion rotated = (*this) * qv * this->inverse();
        return {rotated.x, rotated.y, rotated.z};
    }
};

} // namespace stemaj

#endif // __QUATERNION_HPP
