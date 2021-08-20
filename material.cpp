#include "material.h"

material::material() : col(color(1, 1, 1)), ambient(0.1f), diffuse(0.9f), specular(0.9f), shininess(200.0f) {
    // Default values in initializer list
}

bool operator==(material m1, material m2) {
    // TODO: Should ids be used here?  Or should materials not have IDS
    return m1.col == m2.col &&
           abs(m1.ambient - m2.ambient) < EPSILON &&
           abs(m1.diffuse - m2.diffuse) < EPSILON &&
           abs(m1.specular - m2.specular) < EPSILON &&
           abs(m1.shininess - m2.shininess) < EPSILON;
}