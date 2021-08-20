#include "intersection.h"

intersection::intersection() {
    // Empty default constructor
}

intersection::intersection(float t, const sphere& s) {
    this->t = t;
    this->object = s;
}   

// Precondition: Assumes i1 and i2 are sorted
int intersections(intersection* i1, int i1Len, intersection* i2, int i2Len, intersection* iOut, int maxOut) {
    if(i1Len + i2Len > maxOut) {
        return -1; // ERROR: length of concatenated intersections would exceed buffer
    }

    // Local copy of each input argument just in case same is passed in as output/i1/i2
    intersection* iOutCopy = new intersection[i1Len + i2Len];

    // Combining sorted arrays but keeping them sorted
    int i1Index = 0;
    int i2Index = 0;
    for(int i = 0; i < i1Len + i2Len; ++i) {
        if(i1Index == i1Len) {
            iOutCopy[i] = i2[i2Index];
            ++i2Index;
        } else if (i2Index == i2Len) {
            iOutCopy[i] = i1[i1Index];
            ++i1Index;
        } else {
            if(i1[i1Index].t <= i2[i2Index].t) {
                iOutCopy[i] = i1[i1Index];
                ++i1Index;
            } else {
                iOutCopy[i] = i2[i2Index];
                ++i2Index;
            }
        }
    }
    for(int i = 0; i < i1Len + i2Len; ++i) {
        iOut[i] = iOutCopy[i];
    }
    delete(iOutCopy);
    return i1Len + i2Len;
}

bool operator==(const intersection& i1, const intersection& i2) {
    return (abs(i1.t - i2.t) < EPSILON) && i1.object == i2.object;
}

bool hit(intersection* xs, int xsLen, intersection& out) {
    for(int i = 0; i < xsLen; ++i) {
        if(xs[i].t >= 0) {
            out = xs[i];
            return true;
        }
    }
    return false;
}