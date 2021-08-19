#ifndef MAT4x4_H
#define MAT4x4_H
#include <iostream>
#include "tup4.h"
#include "mat3x3.h"

class mat4x4 {
    public:
    float values[4][4];

    friend std::ostream& operator<<(std::ostream& os, const mat4x4& dt);
    friend mat4x4 operator*(mat4x4 a, mat4x4 b);
    friend tup4 operator*(mat4x4 a, tup4 b);
    friend bool operator==(mat4x4 a, mat4x4 b);
    friend bool operator !=(mat4x4 a, mat4x4 b);
    float* operator[](int);
};

mat4x4 transpose(mat4x4);
mat3x3 submatrix(mat4x4, int, int);
float mat_minor(mat4x4, int, int); // Strange name due to name conflict with built-in macro "minor"
float cofactor(mat4x4, int, int);
float determinant(mat4x4);
mat4x4 inverse(mat4x4);

#endif