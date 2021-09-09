#pragma once

#include <math.h>

template <typename T>
struct Vec2
{
    T x = 0;
    T y = 0;
    Vec2();
    Vec2(T x, T y) : x(x), y(y){};
};