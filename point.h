#ifndef POINT_H
#define POINT_H
#include "tup4.h"

class point : public tup4 {
    public:
    point();
    point(float, float, float);
    point(const tup4&);
};
#endif