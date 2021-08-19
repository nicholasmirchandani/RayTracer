#include "color.h"

color::color() : tup3(0, 0, 0) {
    // Initialization list is all we need
}

color::color(float r, float g, float b) : tup3(r, g, b) {
    // Initialization list is all we need
}

color operator+(color c1, color c2) {
    // TODO: Implement alpha blending properly.  For now just adding r g and b values and assuming alpha = 1
    return color(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b);
}

color operator-(color c1, color c2) {
    // TODO: Implement alpha blending properly.  For now just subtracting r g and b values and assuming alpha = 1
    return color(c1.r - c2.r, c1.g - c2.g, c1.b - c2.b);
}

color operator*(float c, color c1) {
    // TODO: How does alpha affect this?
    return color(c * c1.r, c * c1.g, c * c1.b);
}

color operator*(color c1, float c) {
    // TODO: How does alpha affect this?
    return color(c * c1.r, c * c1.g, c * c1.b);
}

color operator*(color c1, color c2) {
    // TODO: How does alpha affect this?
    return color(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b);
}