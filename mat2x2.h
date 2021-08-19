#ifndef MAT2x2_H
#define MAT2x2_H
#include <iostream>
#include "tup2.h"

#define MAT2x2_INIT(mat, A, B, \
                         C, D) \
                         mat[0][0] = A; mat[0][1] = B; \
                         mat[1][0] = C; mat[1][1] = D;

class mat2x2 {
    public:
    float values[2][2];

    friend std::ostream& operator<<(std::ostream& os, const mat2x2& dt);
    friend mat2x2 operator*(mat2x2 a, mat2x2 b);
    friend tup2 operator*(mat2x2 a, tup2 b);
    friend bool operator==(mat2x2 a, mat2x2 b);
    friend bool operator !=(mat2x2 a, mat2x2 b);
    float* operator[](int);
};

mat2x2 transpose(mat2x2);
float determinant(mat2x2);
#endif