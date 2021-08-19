#ifndef COLOR_H
#define COLOR_H
#include "tup3.h"

class color : public tup3 {
    public:
    color();
    color(float, float, float);

    friend color operator+(color, color);
    friend color operator-(color, color);
    friend color operator*(float, color);
    friend color operator*(color, float);
    friend color operator*(color, color);
};

#endif