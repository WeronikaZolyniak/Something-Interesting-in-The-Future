#pragma once
#include <iostream>

struct Vector2
{
    float x;
    float y;

    void Normalize()
    {
        if (x == 0 && y == 0) return;

        float L = sqrt(x * x + y * y);
        x = x / L;
        y = y / L;
    }

    void operator+=(Vector2 v)
    {
        x += v.x;
        y += v.y;
    }

    void operator-=(Vector2 v)
    {
        x -= v.x;
        y -= v.y;
    }

    /*Vector2& operator*(float value)
    {
        x *= value;
        y *= value;
        return *this;
    }*/

};

Vector2 operator*(Vector2 v1, Vector2 v2);

Vector2 operator*(Vector2 v1, float value);

bool operator!=(Vector2 v1, Vector2 v2);
