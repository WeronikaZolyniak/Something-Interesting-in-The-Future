#include "Vector.h"

Vector2 operator*(Vector2 v1, Vector2 v2)
{
    Vector2 v;
    v.x = v1.x * v2.y;
    v.y = v1.y * v2.y;
    return v;
}

Vector2 operator*(Vector2 v1, float value)
{
    Vector2 v;
    v.x = v1.x * value;
    v.y = v1.y * value;
    return v;
}

bool operator!=(Vector2 v1, Vector2 v2)
{
    return (v1.x != v2.x || v1.y != v2.y);
}
