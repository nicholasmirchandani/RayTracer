#ifndef CANVAS_H
#define CANVAS_H
#include "color.h"

class canvas {
    public:
    color** pixels;
    int width;
    int height;
    canvas(int, int);
    ~canvas();

    std::string ToPPM();
    void writePPM(std::ofstream&);
    // Operator overloading canvas[width][height] to be canvas.pixels[width][height]
    color* operator[](int);

};
#endif