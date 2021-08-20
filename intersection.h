#ifndef INTERSECTION_H
#define INTERSECTION_H
#include "sphere.h"

class intersection {
    public:
        float t;
        sphere object; // TODO: Generalize this to an Object that isn't necessarily a sphere

        intersection();
        intersection(float, const sphere&);
        friend bool operator==(const intersection&, const intersection&);
};

int intersections(intersection* i1, int i1Len, intersection* i2, int i2Len, intersection* iOut, int maxOut);
bool hit(intersection* xs, int xsLen, intersection& out);

#endif