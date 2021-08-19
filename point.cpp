#include "point.h"

point::point(float x, float y, float z) : tup4(x, y, z, 1.0f) {
    // Initialization list is all we need
}
point::point(const tup4& t) : tup4(t) {
    // Initialization list is all we ned
}