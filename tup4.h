#ifndef TUP4_H
#define TUP4_H
#define EPSILON 0.00001f
#include <iostream>
#include <cmath>

class tup4 {
    public:
    union {
        struct {float x, y, z, w;};
        struct {float r, g, b, a;};
        float values[4];
    };

    tup4();
    tup4(float, float, float, float);
    bool isPoint();
    friend std::ostream& operator<<(std::ostream& os, const tup4& dt);
    friend tup4 operator+(tup4 a1, tup4 a2);
    friend tup4 operator-(tup4 a1, tup4 a2);
    friend bool operator==(tup4 a1, tup4 a2);
    friend tup4 operator-(tup4 a1);
    friend tup4 operator*(float c, tup4 a1);
    friend tup4 operator*(tup4 a1, float c);
    friend tup4 operator/(tup4 a1, float c);
    float operator[](int i);
};

// NOTE: Although these are only meant to be used with vectors, they're implemented to be used with generic tup4s for speed
float magnitude(tup4 t); // Just declaration so main knows it exists; implementation is in tup4.cpp
tup4 normalize(tup4 t);
float dot(tup4 a1, tup4 a2);
tup4 cross(tup4 a1, tup4 a2);
#endif