#ifndef TUP3_H
#define TUP3_H
#define EPSILON 0.00001f
#include <iostream>
#include <cmath>

class tup3 {
    public:
    union {
        struct {float x, y, z;};
        struct {float r, g, b;};
        float values[3];
    };

    tup3();
    tup3(float, float, float);
    friend std::ostream& operator<<(std::ostream& os, const tup3& dt);
    friend tup3 operator+(tup3 a1, tup3 a2);
    friend tup3 operator-(tup3 a1, tup3 a2);
    friend bool operator==(tup3 a1, tup3 a2);
    friend tup3 operator-(tup3 a1);
    friend tup3 operator*(float c, tup3 a1);
    friend tup3 operator*(tup3 a1, float c);
    friend tup3 operator/(tup3 a1, float c);
    float operator[](int i);
};
#endif