#include "Vector.h"

Vector2 operator*(Vector2 v1, Vector2 v2)
{
    Vector2 v;
    v.x = v1.x * v2.y;
    v.y = v1.y * v2.y;
    return v;
}