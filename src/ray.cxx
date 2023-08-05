#include <ray.hxx>
#include <vec2.hxx>
#include <cmath>

using std::optional;
using std::nullopt;

Ray::Ray(Creature const *self, Vec2 origin, Vec2 direction) : creature(self), origin(origin),
                                                              direction(direction / direction.norm()) {}

Vec2 Ray::get_point(double t) const {
    return origin + direction * t;
}


double Ray::collide_with_circle(Vec2 center, double radius) const {
    Vec2 oc = origin - center;
    double a = direction.dot(direction);
    double b = 2.0 * oc.dot(direction);
    double c = oc.dot(oc) - radius * radius;
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return NO_COLLISION;
    } else {
        double t1 = (-b - sqrt(discriminant)) / (2.0 * a);
        double t2 = (-b + sqrt(discriminant)) / (2.0 * a);
        if (t1 > 0) {
            return t1;
        } else if (t2 > 0) {
            return t2;
        } else {
            return Ray::NO_COLLISION;
        }
    }
}
