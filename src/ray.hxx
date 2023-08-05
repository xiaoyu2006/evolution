#ifndef RAY_HXX
#define RAY_HXX

class Ray;

#include <vec2.hxx>
#include <creature.hxx>
#include <optional>

class Ray {
public:
    Ray(Creature const *self, Vec2 origin, Vec2 direction);

    Vec2 get_point(double t) const;

    // Collision with circle, returns the t value of the collision, or NO_COLLISION if there is no collision
    // t is guaranteed to be positive
    double collide_with_circle(Vec2 center, double radius) const;

    Vec2 origin;
    Vec2 direction;
    Creature const *creature = nullptr;
    static constexpr double NO_COLLISION = -1.0;
};


#endif
