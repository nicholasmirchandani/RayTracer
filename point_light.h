#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H
#include "color.h"
#include "point.h"
#include "material.h"
#include "vector.h"

class point_light {
    public:
        color intensity;
        point position;
        point_light(point, color);
};

color lighting(material m, point_light light, point position, vector eyev, vector normalv);

#endif