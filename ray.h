#ifndef RAY_H
#define RAY_H
#include "point.h"
#include "vector.h"
#include "sphere.h"
#include "intersection.h"

class ray {
    public:
    point origin;
    vector direction;

    ray();
    ray(const point& p, const vector& v);
};

point position(const ray& r, float t);
// Nonallocating intersect function takes buffer and its length as input, returns the count of intersections, and writes them to the array  
int intersect(const ray& r, const sphere& s, intersection* out, int bufLen);
ray transform(const ray& r, const mat4x4& m);
#endif