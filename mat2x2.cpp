#include "mat2x2.h"

float* mat2x2::operator[](int i) {
    return values[i];
}

std::ostream& operator<<(std::ostream& os, const mat2x2& m) {
    for(int i = 0; i < 2; ++i) {
        os << "[ ";
        for(int j = 0; j < 2; ++j) {
            os << m.values[i][j] << " ";
        }
        os << "]\n";
    }
    return os;
}

mat2x2 operator*(mat2x2 a, mat2x2 b) {
    mat2x2 M;
    for(int i = 0; i < 2 /*a.height*/; ++i) {
        for(int j = 0; j < 2 /*b.width*/; ++j) {
            M[i][j] = 0;
            for(int k = 0; k < 2 /*a.width*/; ++k) {
                M[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return M;
}

tup2 operator*(mat2x2 a, tup2 b) {
    tup2 t;
    t.x = 0;
    t.y = 0;
    for(int k = 0; k < 2 /*a.width*/; ++k) {
        t.x += a[0][k] * b[k];
        t.y += a[1][k] * b[k];
    }
    return t;
}

bool operator==(mat2x2 a, mat2x2 b) {
    for(int i = 0; i < 2; ++i) {
        for(int j = 0; j < 2; ++j) {
            if(abs(a[i][j] - b[i][j]) >= EPSILON) {
                return false;
            }
        }
    }
    return true;
}

bool operator !=(mat2x2 a, mat2x2 b) {
    return !(a == b);
}

mat2x2 transpose(mat2x2 a) {
    mat2x2 result;
    for(int i = 0; i < 2; ++i) {
        for(int j = 0; j < 2; ++j) {
            result[j][i] = a[i][j];
        }
    }
    return result;
}

float determinant(mat2x2 a) {
    return a[0][0] * a[1][1] - a[0][1] * a[1][0];
}