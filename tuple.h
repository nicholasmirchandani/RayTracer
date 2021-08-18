#ifndef TUPLE_H
#define TUPLE_H
#define EPSILON 0.00001f
#include <iostream>
#include <cmath>

class tuple {
    public:
    union {
        struct {float x, y, z, w;};
        struct {float r, g, b, a;};
    };

    tuple();
    tuple(float, float, float, float);
    bool isPoint();
    friend std::ostream& operator<<(std::ostream& os, const tuple& dt);
    friend tuple operator+(tuple a1, tuple a2);
    friend tuple operator-(tuple a1, tuple a2);
    friend bool operator==(tuple a1, tuple a2);
    friend tuple operator-(tuple a1);
    friend tuple operator*(float c, tuple a1);
    friend tuple operator*(tuple a1, float c);
    friend tuple operator/(tuple a1, float c);
};

// NOTE: Although these are only meant to be used with vectors, they're implemented to be used with generic tuples for speed
float magnitude(tuple t); // Just declaration so main knows it exists; implementation is in tuple.cpp
tuple normalize(tuple t);
float dot(tuple a1, tuple a2);
tuple cross(tuple a1, tuple a2);
#endif