#ifndef MAT4x4_H
#define MAT4x4_H
#include <iostream>
#include "tup4.h"
#include "mat3x3.h"

#define MAT4X4_INIT(mat, A, B, C, D, \
                         E, F, G, H, \
                         I, J, K, L, \
                         M, N, O, P) \
                         mat[0][0] = A; mat[0][1] = B; mat[0][2] = C; mat[0][3] = D; \
                         mat[1][0] = E; mat[1][1] = F; mat[1][2] = G; mat[1][3] = H; \
                         mat[2][0] = I; mat[2][1] = J; mat[2][2] = K; mat[2][3] = L; \
                         mat[3][0] = M; mat[3][1] = N; mat[3][2] = O; mat[3][3] = P;

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