#ifndef VECTOR_H
#define VECTOR_H
#include "tup4.h"

class vector : public tup4 {
    public:
    vector();
    vector(float, float, float);
    vector(const tup4&);
};
#endif