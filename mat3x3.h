#ifndef MAT3x3_H
#define MAT3x3_H
#include <iostream>
#include "tup3.h"
#include "mat2x2.h"

#define MAT3x3_INIT(mat, A, B, C, \
                         D, E, F, \
                         G, H, I) \
                         mat[0][0] = A; mat[0][1] = B; mat[0][2] = C; \
                         mat[1][0] = D; mat[1][1] = E; mat[1][2] = F; \
                         mat[2][0] = G; mat[2][1] = H; mat[2][2] = I;

class mat3x3 {
    public:
    float values[3][3];

    friend std::ostream& operator<<(std::ostream& os, const mat3x3& dt);
    friend mat3x3 operator*(mat3x3 a, mat3x3 b);
    friend tup3 operator*(mat3x3 a, tup3 b);
    friend bool operator==(mat3x3 a, mat3x3 b);
    friend bool operator !=(mat3x3 a, mat3x3 b);
    float* operator[](int);
};

mat3x3 transpose(mat3x3);
mat2x2 submatrix(mat3x3, int, int);
float mat_minor(mat3x3, int, int); // Strange name due to name conflict with built-in macro "minor"
float cofactor(mat3x3, int, int);
float determinant(mat3x3);
#endif