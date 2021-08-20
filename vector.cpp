#include "vector.h"

vector::vector() {
    // Nothing is guaranteed by default
}

vector::vector(float x, float y, float z) : tup4(x, y, z, 0.0f) {
    // Initialization list is all we need
}

vector::vector(const tup4& t) : tup4(t) {
    // Initialization list is all we need
}