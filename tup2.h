#ifndef TUP2_H
#define TUP2_H
#define EPSILON 0.00001f
#include <iostream>
#include <cmath>

class tup2 {
    public:
    union {
        struct {float x, y;};
        struct {float r, g;};
        float values[3];
    };

    tup2();
    tup2(float, float);
    friend std::ostream& operator<<(std::ostream& os, const tup2& dt);
    friend tup2 operator+(tup2 a1, tup2 a2);
    friend tup2 operator-(tup2 a1, tup2 a2);
    friend bool operator==(tup2 a1, tup2 a2);
    friend tup2 operator-(tup2 a1);
    friend tup2 operator*(float c, tup2 a1);
    friend tup2 operator*(tup2 a1, float c);
    friend tup2 operator/(tup2 a1, float c);
    float operator[](int i);
};
#endif