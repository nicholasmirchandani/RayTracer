#include "tup4.h"

tup4::tup4() {
    // Nada
}

tup4::tup4(float x, float y, float z, float w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

tup4::tup4(const tup4& t) {
    x = t.x;
    y = t.y;
    z = t.z;
    w = t.w;
}

bool tup4::isPoint() {
    return w == 1.0f;
}


std::ostream& operator<<(std::ostream& os, const tup4& t) {
    os << "(" << t.x << ", " << t.y << ", " << t.z << ", " << t.w << ")";
    return os;
}

tup4 operator+(tup4 a1, tup4 a2) {
    return tup4(a1.x + a2.x, a1.y + a2.y, a1.z + a2.z, a1.w + a2.w);
}

tup4 operator-(tup4 a1, tup4 a2) {
    return tup4(a1.x - a2.x, a1.y - a2.y, a1.z - a2.z, a1.w - a2.w);
}

bool operator==(tup4 a1, tup4 a2) {
    bool xEq = abs(a1.x - a2.x) < EPSILON;
    bool yEq = abs(a1.y - a2.y) < EPSILON;
    bool zEq = abs(a1.z - a2.z) < EPSILON;
    bool wEq = abs(a1.w - a2.w) < EPSILON;
    return xEq && yEq && zEq && wEq;
}

tup4 operator-(tup4 a1) {
    return tup4(-1 * a1.x, -1 * a1.y, -1 * a1.z, -1 * a1.w);
}

tup4 operator*(float c, tup4 a1) {
    return tup4(c * a1.x, c * a1.y, c * a1.z, c * a1.w);
}

tup4 operator*(tup4 a1, float c) {
    return tup4(c * a1.x, c * a1.y, c * a1.z, c * a1.w);
}

tup4 operator/(tup4 a1, float c) {
    return a1 * (1/c);
}

float tup4::operator[](int i) {
    return values[i];
}

float magnitude(tup4 t) {
    return sqrt(t.x * t.x + t.y * t.y + t.z * t.z + t.w * t.w);
}

tup4 normalize(tup4 t) {
    float magT = magnitude(t);
    return tup4(t.x / magT, t.y / magT, t.z / magT, t.w / magT);
}

float dot(tup4 a1, tup4 a2) {
    return  a1.x * a2.x +
            a1.y * a2.y + 
            a1.z * a2.z +
            a1.w * a2.w;
}

tup4 cross(tup4 a1, tup4 a2) {
    // NOTE: if either is a point this will just assume it's a vector, and it returns a vector
    return tup4(a1.y * a2.z - a1.z * a2.y,
                  a1.z * a2.x - a1.x * a2.z,
                  a1.x * a2.y - a1.y * a2.x, 0.0f);
}

tup4 reflect(tup4 in, tup4 normal) {
    return in - normal * 2 * dot(in, normal);
}