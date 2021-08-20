#ifndef MATERIAL_H
#define MATERIAL_H
#include "color.h"
class material {
    public:
        color col;
        float ambient;
        float diffuse;
        float specular;
        float shininess;
        material();

        friend bool operator==(material, material);
};
#endif