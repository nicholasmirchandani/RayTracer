#ifndef COLOR_H
#define COLOR_H
#include "tuple.h"

class color : public tuple {
    public:
    color();
    color(float, float, float);
    color(float, float, float, float);

    friend color operator+(color, color);
    friend color operator-(color, color);
    friend color operator*(float, color);
    friend color operator*(color, float);
    friend color operator*(color, color);
};

#endif