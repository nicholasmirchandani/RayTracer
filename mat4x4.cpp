#include "mat4x4.h"

float* mat4x4::operator[](int i) {
    return values[i];
}

std::ostream& operator<<(std::ostream& os, const mat4x4& m) {
    for(int i = 0; i < 4; ++i) {
        os << "[ ";
        for(int j = 0; j < 4; ++j) {
            os << m.values[i][j] << " ";
        }
        os << "]\n";
    }
    return os;
}

mat4x4 operator*(mat4x4 a, mat4x4 b) {
    mat4x4 M;
    for(int i = 0; i < 4 /*a.height*/; ++i) {
        for(int j = 0; j < 4 /*b.width*/; ++j) {
            M[i][j] = 0;
            for(int k = 0; k < 4 /*a.width*/; ++k) {
                M[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return M;
}

tup4 operator*(mat4x4 a, tup4 b) {
    tup4 t;
    t.x = 0;
    t.y = 0;
    t.z = 0;
    t.w = 0;
    for(int k = 0; k < 4 /*a.width*/; ++k) {
        t.x += a[0][k] * b[k];
        t.y += a[1][k] * b[k];
        t.z += a[2][k] * b[k];
        t.w += a[3][k] * b[k];
    }
    return t;
}

bool operator==(mat4x4 a, mat4x4 b) {
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            if(abs(a[i][j] - b[i][j]) >= EPSILON) {
                return false;
            }
        }
    }
    return true;
}

bool operator!=(mat4x4 a, mat4x4 b) {
    return !(a == b);
}

mat4x4 transpose(mat4x4 a) {
    mat4x4 result;
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            result[j][i] = a[i][j];
        }
    }
    return result;
}

mat3x3 submatrix(mat4x4 a, int row, int col) {
    mat3x3 result;
    int curRow = 0;
    for(int i = 0; i < 4; ++i) {
        int curCol = 0;
        if(i == row) {
            continue;
        }
        for(int j = 0; j < 4; ++j) {
            if(j == col) {
                continue;
            }
            result[curRow][curCol] = a[i][j];
            ++curCol;
        }
        ++curRow;
    }

    return result;
}

float mat_minor(mat4x4 a, int row, int col) {
    return determinant(submatrix(a, row, col));
}

float cofactor(mat4x4 a, int row, int col) {
    if ((row + col) % 2 == 0) {
        return mat_minor(a, row, col);
    } else {
        return -1 * mat_minor(a, row, col);
    }
}

float determinant(mat4x4 a) {
    return a[0][0] * cofactor(a, 0, 0) + a[0][1] * cofactor(a, 0, 1) + a[0][2] * cofactor(a, 0, 2) + a[0][3] * cofactor(a, 0, 3);
}

mat4x4 inverse(mat4x4 a) {
    mat4x4 result;

    float detA = determinant(a);
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            result[i][j] = cofactor(a, j, i) / detA;
        }
    }
    return result;
}