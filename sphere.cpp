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
    // Initializer List is all we need.  Used to avoid errors due to missing point default constructor
}

bool operator==(const sphere& s1, const sphere& s2) {
    // TODO: Could you just check the ids?  I think so, unless you have more ids than int has memory... which is more than I'd ever use
    // return (abs(s1.radius - s2.radius) < EPSILON) && (s1.origin == s2.origin) && s1.id == s2.id;
    return s1.id == s2.id;
}