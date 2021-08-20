#ifndef SPHERE_H
#define SPHERE_H
#include "point.h"
#include "vector.h"
#include "mat4x4.h"
#include "material.h"

class sphere {
    public:
        mat4x4 transform;
        material mat;
        unsigned int id;

    sphere();
    friend bool operator==(const sphere&, const sphere&);
};

vector normal_at(sphere, point);
#endif