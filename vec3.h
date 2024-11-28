// File is only processed once by the compiler, even if it is included multiple times
#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class vec3 {
public:
    double e[3];

    // Default constructor
    vec3() : e{ 0, 0, 0 } {}

    // Constructor with member initializer list for efficiency
    vec3(double e0, double e1, double e2) : e{ e0, e1, e2 } {}

    // Accessor methods for components
    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    // Negation operator
    vec3 operator-() const {
        return vec3(-e[0], -e[1], -e[2]);
    }

    // Access element (const version)
    double operator[](int i) const {
        return e[i];
    }

    // Access element (modifiable version)
    double& operator[](int i) {
        return e[i];
    }

    // Overload += operator
    vec3& operator+=(const vec3& v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    // Compute the length of the vector
    double length() const {
        return std::sqrt(length_squared());
    }

    // Compute the squared length of the vector
    double length_squared() const {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }
};

// Alias for vec3 to represent 3D points
using point3 = vec3;

// Inline suggestion to the compiler to replace a function call with the actual code of the function, 
// effectively embedding the function's code directly at the point of use
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}
inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3& v) {
    return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(const vec3& v, double t) {
    return t * v;
}

inline vec3 operator/(const vec3& v, double t) {
    return (1 / t) * v;
}

inline double dot(const vec3& u, const vec3& v) {
    return u.e[0] * v.e[0]
        + u.e[1] * v.e[1]
        + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
        u.e[2] * v.e[0] - u.e[0] * v.e[2],
        u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}

#endif

