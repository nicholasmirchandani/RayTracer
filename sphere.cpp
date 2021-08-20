#include "sphere.h"

sphere::sphere() {
    static unsigned int idGen = 0;
    id = idGen;
    ++idGen;
    MAT4X4_INIT(transform,
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1);
    mat = material();
}

bool operator==(const sphere& s1, const sphere& s2) {
    // Could you just check the ids?  I think so, unless you have more ids than int has memory... which is more than I'd ever use
    // return (abs(s1.radius - s2.radius) < EPSILON) && (s1.origin == s2.origin) && s1.id == s2.id;
    return s1.id == s2.id;
}

vector normal_at(sphere s, point p) {
    // Optimization; don't worry about normalizing or subtracting the origin since it's the unit sphere
    p = inverse(s.transform) * p;
    vector object_normal = normalize(p - point(0, 0, 0)); // Subtract the origin, 0,0,0, from the point and return it
    vector world_normal = transpose(inverse(s.transform)) * object_normal; // Converting from object_normal to world_normal
    world_normal.w = 0;
    return normalize(world_normal);
}