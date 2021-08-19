#include "tup2.h"

tup2::tup2() {
    // Nada
}

tup2::tup2(float x, float y) {
    this->x = x;
    this->y = y;
}


std::ostream& operator<<(std::ostream& os, const tup2& t) {
    os << "(" << t.x << ", " << t.y << ")";
    return os;
}

tup2 operator+(tup2 a1, tup2 a2) {
    return tup2(a1.x + a2.x, a1.y + a2.y);
}

tup2 operator-(tup2 a1, tup2 a2) {
    return tup2(a1.x - a2.x, a1.y - a2.y);
}

bool operator==(tup2 a1, tup2 a2) {
    bool xEq = abs(a1.x - a2.x) < EPSILON;
    bool yEq = abs(a1.y - a2.y) < EPSILON;
    return xEq && yEq;
}

tup2 operator-(tup2 a1) {
    return tup2(-1 * a1.x, -1 * a1.y);
}

tup2 operator*(float c, tup2 a1) {
    return tup2(c * a1.x, c * a1.y);
}

tup2 operator*(tup2 a1, float c) {
    return tup2(c * a1.x, c * a1.y);
}

tup2 operator/(tup2 a1, float c) {
    return a1 * (1/c);
}

float tup2::operator[](int i) {
    return values[i];
}