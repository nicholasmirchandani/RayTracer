#include "tuple.h"

tuple::tuple() {
    // Nada
}

tuple::tuple(float x, float y, float z, float w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

bool tuple::isPoint() {
    return w == 1.0f;
}


std::ostream& operator<<(std::ostream& os, const tuple& t) {
    os << "(" << t.x << ", " << t.y << ", " << t.z << ", " << t.w << ")";
    return os;
}

tuple operator+(tuple a1, tuple a2) {
    return tuple(a1.x + a2.x, a1.y + a2.y, a1.z + a2.z, a1.w + a2.w);
}

tuple operator-(tuple a1, tuple a2) {
    return tuple(a1.x - a2.x, a1.y - a2.y, a1.z - a2.z, a1.w - a2.w);
}

bool operator==(tuple a1, tuple a2) {
    bool xEq = abs(a1.x - a2.x) < EPSILON;
    bool yEq = abs(a1.y - a2.y) < EPSILON;
    bool zEq = abs(a1.z - a2.z) < EPSILON;
    bool wEq = abs(a1.w - a2.w) < EPSILON;
    return xEq && yEq && zEq && wEq;
}

tuple operator-(tuple a1) {
    return tuple(-1 * a1.x, -1 * a1.y, -1 * a1.z, -1 * a1.w);
}

tuple operator*(float c, tuple a1) {
    return tuple(c * a1.x, c * a1.y, c * a1.z, c * a1.w);
}

tuple operator*(tuple a1, float c) {
    return tuple(c * a1.x, c * a1.y, c * a1.z, c * a1.w);
}

tuple operator/(tuple a1, float c) {
    return a1 * (1/c);
}

float magnitude(tuple t) {
    return sqrt(t.x * t.x + t.y * t.y + t.z * t.z + t.w * t.w);
}

tuple normalize(tuple t) {
    float magT = magnitude(t);
    return tuple(t.x / magT, t.y / magT, t.z / magT, t.w / magT);
}

float dot(tuple a1, tuple a2) {
    return  a1.x * a2.x +
            a1.y * a2.y + 
            a1.z * a2.z +
            a1.w * a2.w;
}

tuple cross(tuple a1, tuple a2) {
    // NOTE: if either is a point this will just assume it's a vector, and it returns a vector
    return tuple(a1.y * a2.z - a1.z * a2.y,
                  a1.z * a2.x - a1.x * a2.z,
                  a1.x * a2.y - a1.y * a2.x, 0.0f);
}