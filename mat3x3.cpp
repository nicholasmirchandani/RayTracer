#include "mat3x3.h"

float* mat3x3::operator[](int i) {
    return values[i];
}

std::ostream& operator<<(std::ostream& os, const mat3x3& m) {
    for(int i = 0; i < 3; ++i) {
        os << "[ ";
        for(int j = 0; j < 3; ++j) {
            os << m.values[i][j] << " ";
        }
        os << "]\n";
    }
    return os;
}

mat3x3 operator*(mat3x3 a, mat3x3 b) {
    mat3x3 M;
    for(int i = 0; i < 3 /*a.height*/; ++i) {
        for(int j = 0; j < 3 /*b.width*/; ++j) {
            M[i][j] = 0;
            for(int k = 0; k < 3 /*a.width*/; ++k) {
                M[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return M;
}

tup3 operator*(mat3x3 a, tup3 b) {
    tup3 t;
    t.x = 0;
    t.y = 0;
    t.z = 0;
    for(int k = 0; k < 3 /*a.width*/; ++k) {
        t.x += a[0][k] * b[k];
        t.y += a[1][k] * b[k];
        t.z += a[2][k] * b[k];
    }
    return t;
}

bool operator==(mat3x3 a, mat3x3 b) {
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            if(abs(a[i][j] - b[i][j]) >= EPSILON) {
                return false;
            }
        }
    }
    return true;
}

bool operator !=(mat3x3 a, mat3x3 b) {
    return !(a == b);
}

mat3x3 transpose(mat3x3 a) {
    mat3x3 result;
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            result[j][i] = a[i][j];
        }
    }
    return result;
}

mat2x2 submatrix(mat3x3 a, int row, int col) {
    mat2x2 result;
    int curRow = 0;
    for(int i = 0; i < 3; ++i) {
        int curCol = 0;
        if(i == row) {
            continue;
        }
        for(int j = 0; j < 3; ++j) {
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

float mat_minor(mat3x3 a, int row, int col) {
    return determinant(submatrix(a, row, col));
}

float cofactor(mat3x3 a, int row, int col) {
    if ((row + col) % 2 == 0) {
        return mat_minor(a, row, col);
    } else {
        return -1 * mat_minor(a, row, col);
    }
}

float determinant(mat3x3 a) {
    return a[0][0] * cofactor(a, 0, 0) + a[0][1] * cofactor(a, 0, 1) + a[0][2] * cofactor(a, 0, 2);
}