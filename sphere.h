#ifndef SPHERE_H
#define SPHERE_H
#include "point.h"
#include "mat4x4.h"

class sphere {
    public:
        mat4x4 transform;
        unsigned int id;

    sphere();
    friend bool operator==(const sphere&, const sphere&);
};

#endif