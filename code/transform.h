#include "Vector2D.h"

class Transform
{
public:
    Vector2D position;
    double rotation;
    Vector2D scale;

    Transform() : position(0, 0), rotation(0), scale(1, 1) {}
    Transform(const Vector2D &pos, double rot, const Vector2D &sca)
        : position(pos), rotation(rot), scale(sca)
    {
    }
    Transform &operator+=(const Transform &another)
    {
        position += another.position;
        rotation += another.rotation;
        scale += another.scale;
        return *this;
    }
};