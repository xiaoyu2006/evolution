#ifndef VEC2_HXX
#define VEC2_HXX

#include <string>
#include <util.hxx>

class Vec2 {
public:
    Vec2(double x, double y);

    inline friend Vec2 operator+(Vec2 const &v1, Vec2 const &v2) {
        return {v1.x + v2.x, v1.y + v2.y};
    }

    inline friend Vec2 operator-(Vec2 const &v1, Vec2 const &v2) {
        return {v1.x - v2.x, v1.y - v2.y};
    }

    inline friend Vec2 operator*(Vec2 const &v, double scalar) {
        return {v.x * scalar, v.y * scalar};
    }

    inline friend Vec2 operator/(Vec2 const &v, double scalar) {
        return {v.x / scalar, v.y / scalar};
    }

    inline friend bool operator==(Vec2 const &v1, Vec2 const &v2) {
        return v1.x == v2.x && v1.y == v2.y;
    }

    inline std::string serialize() const {
        return std::to_string(x) + "," + std::to_string(y);
    }

    static inline Vec2 random() {
        return {random_double(), random_double()};
    }

    inline double dot(Vec2 const &v) const {
        return x * v.x + y * v.y;
    }

    inline double norm_sqr() const {
        return x * x + y * y;
    }

    inline double norm() const {
        return sqrt(norm_sqr());
    }

    inline double dist(Vec2 const &v) const {
        return (*this - v).norm();
    }

    double x;
    double y;

    static inline Vec2 from_angle(double angle) {
        return {cos(angle), sin(angle)};
    }
};

#endif
