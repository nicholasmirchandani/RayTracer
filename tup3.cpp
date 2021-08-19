#include "tup3.h"

tup3::tup3() {
    // Nada
}

tup3::tup3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}


std::ostream& operator<<(std::ostream& os, const tup3& t) {
    os << "(" << t.x << ", " << t.y << ", " << t.z << ")";
    return os;
}

tup3 operator+(tup3 a1, tup3 a2) {
    return tup3(a1.x + a2.x, a1.y + a2.y, a1.z + a2.z);
}

tup3 operator-(tup3 a1, tup3 a2) {
    return tup3(a1.x - a2.x, a1.y - a2.y, a1.z - a2.z);
}

bool operator==(tup3 a1, tup3 a2) {
    bool xEq = abs(a1.x - a2.x) < EPSILON;
    bool yEq = abs(a1.y - a2.y) < EPSILON;
    bool zEq = abs(a1.z - a2.z) < EPSILON;
    return xEq && yEq && zEq;
}

tup3 operator-(tup3 a1) {
    return tup3(-1 * a1.x, -1 * a1.y, -1 * a1.z);
}

tup3 operator*(float c, tup3 a1) {
    return tup3(c * a1.x, c * a1.y, c * a1.z);
}

tup3 operator*(tup3 a1, float c) {
    return tup3(c * a1.x, c * a1.y, c * a1.z);
}

tup3 operator/(tup3 a1, float c) {
    return a1 * (1/c);
}

float tup3::operator[](int i) {
    return values[i];
}