#define RUN_TESTS

#include <iostream>
#include <fstream>
#include <cassert>
#include "tup4.h"
#include "point.h"
#include "vector.h"
#include "color.h"
#include "canvas.h"
#include "mat2x2.h"
#include "mat3x3.h"
#include "mat4x4.h"

int main() {

    #ifdef RUN_TESTS
    { // Chapter 1: Tuples, Points, and Vectors
        { // Test 1: constructing a tuple functions properly.  w = 1.0f means it's a point, w = 0.0f means it's a vector
            // Doing float comparison using epsilon as defined in tup4.h
            tup4 a(4.3, -4.2, 3.1, 1.0);
            bool xEq = abs(a.x - 4.3) < EPSILON;
            bool yEq = abs(a.y - -4.2) < EPSILON;
            bool zEq = abs(a.z - 3.1) < EPSILON;
            bool wEq = abs(a.w - 1.0) < EPSILON;
            assert(xEq && yEq && zEq && wEq);
            assert(a.isPoint());

            tup4 b(4.3, -4.2, 3.1, 0.0);
            xEq = abs(b.x - 4.3) < EPSILON;
            yEq = abs(b.y - -4.2) < EPSILON;
            zEq = abs(b.z - 3.1) < EPSILON;
            wEq = abs(b.w - 0.0) < EPSILON;
            assert(xEq && yEq && zEq && wEq);
            assert(!b.isPoint());
        }
        
        { // Test 2: Point and vector shorthands as tuple 
            point p(4, -4, 3);
            assert(p == tup4(4, -4, 3, 1));
            assert(p.isPoint());
            vector v(4, -4, 3);
            assert(v == tup4(4, -4, 3, 0));
            assert(!v.isPoint());
        }

        { // Test 3: Tuple Arithmetic: Addition, subtraction, negation, and scalar multiplication
            tup4 a1(3, -2, 5, 1);
            tup4 a2(-2, 3, 1, 0);
            assert(a1 + a2 == tup4(1, 1, 6, 1));

            point p1(3, 2, 1);
            point p2(5, 6, 7);
            assert(p1 - p2 == vector(-2, -4, -6));

            point p(3, 2, 1);
            vector v(5, 6, 7);
            assert(p - v == point(-2, -4, -6));

            vector v1(3, 2, 1);
            vector v2(5, 6, 7);
            assert(v1 - v2 == vector(-2, -4, -6));

            tup4 a(1, -2, 3, -4);
            assert(-a == tup4(-1, 2, -3, 4));
            assert(a * 3.5f == tup4(3.5, -7, 10.5, -14));
            assert(3.5f * a == tup4(3.5, -7, 10.5, -14)); // Commutativity test for scalar multiplication
            assert(a * 0.5f == a / 2);
        }

        { // Test 4: Magnitude
            vector v(1, 0, 0);
            assert(abs(magnitude(v) - 1.0f) < EPSILON);
            vector v1(0, 1, 0);
            assert(abs(magnitude(v1) - 1.0f) < EPSILON);
            vector v2(0, 0, 1);
            assert(abs(magnitude(v2) - 1.0f) < EPSILON);
            vector v3(1, 2, 3);
            assert(abs(magnitude(v3) - sqrt(14)) < EPSILON);
            vector v4(-1, -2, -3);
            assert(abs(magnitude(v4) - sqrt(14)) < EPSILON);
        }

        { // Test 5: Normalization
            vector v(4, 0, 0);
            assert(normalize(v) == vector(1, 0, 0));

            v = vector(1, 2, 3);         // Values taken straight from book, approximations
            assert(normalize(v) == vector(0.26726, 0.53452, 0.80178));
        }

        { // Test 6: The dot product
            vector a(1,2,3);
            vector b(2,3,4);
            assert(abs(dot(a,b) - 20) < EPSILON);
        }

        { // Test 7: The cross product
            vector a(1,2,3);
            vector b(2,3,4);
            assert(cross(a,b) == vector(-1, 2, -1));
            assert(cross(b,a) == vector(1, -2, 1));
        }
    }

    { // Chapter 2: Drawing on a Canvas
        { // Test 1: Colors exist with rgb(a)
            color c(-0.5, 0.4, 1.7);
            // Doing float comparison using epsilon as defined in tup4.h
            bool rEq = abs(c.r - -0.5) < EPSILON;
            bool gEq = abs(c.g - 0.4) < EPSILON;
            bool bEq = abs(c.b - 1.7) < EPSILON;
            assert(rEq && gEq && bEq);

            c = color(-0.5, 0.4, 1.7);
            rEq = abs(c.r - -0.5) < EPSILON;
            gEq = abs(c.g - 0.4) < EPSILON;
            bEq = abs(c.b - 1.7) < EPSILON;
            assert(rEq && gEq && bEq);
        }

        { // Test 2: Color Arithmetic; addition, subtraction, scalar multiplication, Hadamart/Schur product
            color c1(0.9, 0.6, 0.75);
            color c2(0.7, 0.1, 0.25);
            assert(c1 + c2 == color(1.6, 0.7, 1.0));
            assert(c1 - c2 == color(0.2, 0.5, 0.5));

            color c(0.2, 0.3, 0.4);
            assert(c * 2 == color(0.4, 0.6, 0.8));
            assert(2 * c == color(0.4, 0.6, 0.8)); //Commutativity of scalar multiplication

            c1 = color(1, 0.2, 0.4);
            c2 = color(0.9, 1, 0.1);
            assert(c1 * c2 == color(0.9, 0.2, 0.04));
        }

        { // Test 3: Canvas creation and pixel modification
            canvas c(10,20);
            assert(c.width == 10 && c.height == 20);
            for(int i = 0; i < c.width; ++i) {
                for(int j = 0; j < c.height; ++j) {
                    assert(c.pixels[i][j] == color(0,0,0));
                }
            }

            color red(1, 0, 0);
            c.pixels[2][3] = red;
            assert(c.pixels[2][3] == red);
        }

        { // Test 4: PPM output 
            {
            canvas c(5, 3);
            color c1(1.5, 0, 0);
            color c2(0, 0.5, 0);
            color c3(-0.5, 0, 1);
            c[0][0] = c1;
            c[2][1] = c2;
            c[4][2] = c3;
            // Note: Spaces at the end of lines are unoptimal but shouldn't pose a problem
            std::string desiredPPM = 
            "P3\n"
            "5 3\n"
            "255\n"
            "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0 \n"
            "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0 \n"
            "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255 \n";
            assert(c.ToPPM() == desiredPPM);
            }

            canvas c(10,2);
            color c1(1, 0.8f, 0.6f);
            for(int i = 0; i < 10; ++i) {
                for(int j = 0; j < 2; ++j) {
                    c[i][j] = c1;
                }
            }
        }
    }

    { // Chapter 3: Matrices
        { // Test 1: Matrices properly set (4x4, 2x2, 3x3)
            {
                mat4x4 M;
                MAT4X4_INIT(M,
                               1,    2,    3,    4,
                            5.5f, 6.5f, 7.5f, 8.5f,
                               9,   10,   11,   12,
                            13.5, 14.5, 15.5, 16.5);

                assert(M[0][0] == 1 && M[0][1] == 2 && M[0][2] == 3 && M[0][3] == 4 && 
                    abs(M[1][0] - 5.5f) < EPSILON && abs(M[1][1] - 6.5f) < EPSILON && abs(M[1][2] - 7.5f) < EPSILON && abs(M[1][3] - 8.5f) < EPSILON &&
                    M[2][0] == 9 && M[2][1] == 10 && M[2][2] == 11 && M[2][3] == 12 &&
                    abs(M[3][0] - 13.5f) < EPSILON && abs(M[3][1] - 14.5f) < EPSILON && abs(M[3][2] - 15.5f) < EPSILON && abs(M[3][3] - 16.5f) < EPSILON);
            }
            {
                mat2x2 M;
                MAT2x2_INIT(M,
                            -3,  5,
                             1, -2);
                assert(M[0][0] == -3 && M[0][1] == 5 && M[1][0] == 1 && M[1][1] == -2);
            }
            {
                mat3x3 M;
                MAT3x3_INIT(M,
                            -3,  5,  0,
                             1, -2, -7,
                             0,  1,  1);
                assert(M[0][0] == -3 && M[0][1] == 5 && M[0][2] == 0 &&
                       M[1][0] == 1 && M[1][1] == -2 && M[1][2] == -7 &&
                       M[2][0] == 0 && M[2][1] == 1 && M[2][2] == 1);
            }
        }

        { // Test 2: Matrix equality
            mat4x4 A;
            MAT4X4_INIT(A,
                         1,  2,  3,  4,
                         5,  6,  7,  8,
                         9,  8,  7,  6,
                         5,  4,  3,  2);

            mat4x4 B;
            MAT4X4_INIT(B,
                         1,  2,  3,  4,
                         5,  6,  7,  8,
                         9,  8,  7,  6,
                         5,  4,  3,  2);

            assert(A == B);

            MAT4X4_INIT(B,
                         2,  3,  4,  5,
                         6,  7,  8,  9,
                         8,  7,  6,  5,
                         4,  3,  2,  1);

            assert (A != B);
        }

        { // Test 3: Matrix multiplication; mat4x4 x mat4x4 and mat4x4 x tup4
            mat4x4 A;
            MAT4X4_INIT(A,
                         1,  2,  3,  4,
                         5,  6,  7,  8,
                         9,  8,  7,  6,
                         5,  4,  3,  2);

            mat4x4 B;
            MAT4X4_INIT(B,
                        -2,  1,  2,  3,
                         3,  2,  1, -1,
                         4,  3,  6,  5,
                         1,  2,  7,  8);

            mat4x4 C = A * B;
            assert(C[0][0] == 20 && C[0][1] == 22 && C[0][2] == 50 && C[0][3] == 48 &&
                   C[1][0] == 44 && C[1][1] == 54 && C[1][2] == 114 && C[1][3] == 108 &&
                   C[2][0] == 40 && C[2][1] == 58 && C[2][2] == 110 && C[2][3] == 102 &&
                   C[3][0] == 16 && C[3][1] == 26 && C[3][2] == 46 && C[3][3] == 42);

            A[0][0] = 1;
            A[0][1] = 2;
            A[0][2] = 3;
            A[0][3] = 4;
            A[1][0] = 2;
            A[1][1] = 4;
            A[1][2] = 4;
            A[1][3] = 2;
            A[2][0] = 8;
            A[2][1] = 6;
            A[2][2] = 4;
            A[2][3] = 1;
            A[3][0] = 0;
            A[3][1] = 0;
            A[3][2] = 0;
            A[3][3] = 1;

            tup4 b(1, 2, 3, 1);

            tup4 c = A * b;
            assert(c[0] == 18 && c[1] == 24 && c[2] == 33 && c[3] == 1);

            mat4x4 ident;
            ident[0][0] = 1;
            ident[0][1] = 0;
            ident[0][2] = 0;
            ident[0][3] = 0;
            ident[1][0] = 0;
            ident[1][1] = 1;
            ident[1][2] = 0;
            ident[1][3] = 0;
            ident[2][0] = 0;
            ident[2][1] = 0;
            ident[2][2] = 1;
            ident[2][3] = 0;
            ident[3][0] = 0;
            ident[3][1] = 0;
            ident[3][2] = 0;
            ident[3][3] = 1;

            assert(ident * A == A);
        }

        { // Test 4: Matrix transposition
            mat4x4 A;
            MAT4X4_INIT(A,
                         0,  9,  3,  0,
                         9,  8,  0,  8,
                         1,  8,  5,  3,
                         0,  0,  5,  8);

            mat4x4 result = transpose(A);
            assert(result[0][0] == 0 && result[0][1] == 9 && result[0][2] == 1 && result[0][3] == 0 &&
                   result[1][0] == 9 && result[1][1] == 8 && result[1][2] == 8 && result[1][3] == 0 &&
                   result[2][0] == 3 && result[2][1] == 0 && result[2][2] == 5 && result[2][3] == 5 &&
                   result[3][0] == 0 && result[3][1] == 8 && result[3][2] == 3 && result[3][3] == 8);

        }

        { // Test 5: Determinant 
            { 
                mat2x2 A;
                MAT2x2_INIT(A,
                             1,  5,
                            -3,  2);
                assert(determinant(A) == 17);
            }

            { 
                mat3x3 A;
                MAT3x3_INIT(A, 
                             1,  5,  0,
                            -3,  2,  7,
                             0,  6, -3);

                mat2x2 B;
                MAT2x2_INIT(B, 
                            -3,  2,
                             0,  6);

                assert(submatrix(A, 0, 2) == B);
            }

            {
                mat4x4 A;
                MAT4X4_INIT(A,
                            -6,  1,  1,  6,
                            -8,  5,  8,  6,
                            -1,  0,  8,  2,
                            -7,  1, -1,  1);
                
                mat3x3 B;
                MAT3x3_INIT(B,
                            -6,  1,  6,
                            -8,  8,  6,
                            -7, -1,  1);
                
                assert(submatrix(A, 2, 1) == B);
            }

            {
                mat3x3 A;
                MAT3x3_INIT(A,
                            3,  5,  0,
                            2, -1, -7,
                            6, -1,  5);
                mat2x2 B = submatrix(A, 1, 0);
                assert(determinant(B) == 25);
                assert(mat_minor(A, 1, 0) == 25);
                assert(cofactor(A, 0, 0) == -12);
                assert(cofactor(A, 1, 0) == -25);
            }

            {
                mat3x3 A;
                MAT3x3_INIT(A,
                             1,  2,  6,
                            -5,  8, -4,
                             2,  6,  4);
                assert(determinant(A) == -196);

                mat4x4 B;
                MAT4X4_INIT(B,
                            -2, -8,  3,  5,
                            -3,  1,  7,  3,
                             1,  2, -9,  6,
                            -6,  7,  7, -9);
                assert(determinant(B) == -4071);
            }
        }

        { // Test 6: Inverse

            {
                mat4x4 A;
                MAT4X4_INIT(A,
                            -5,  2,  6, -8,
                            1, -5,  1,  8,
                            7,  7, -6, -7,
                            1, -3,  7,  4);

                mat4x4 B;
                MAT4X4_INIT(B,
                            0.21805,  0.45113,  0.24060, -0.4511,
                            -0.80827, -1.45677, -0.44361,  0.52068,
                            -0.07895, -0.22368, -0.05263,  0.19737,
                            -0.52256, -0.81391, -0.30075,  0.30639);

                assert(inverse(A) == B);
            }

            {
                mat4x4 A;
                MAT4X4_INIT(A,
                             8, -5,  9,  2,
                             7,  5,  6,  1,
                            -6,  0,  9,  6,
                            -3,  0, -9, -4);
                mat4x4 B;
                MAT4X4_INIT(B,
                            -0.15385, -0.15385, -0.28205, -0.53846,
                            -0.07692,  0.12308,  0.02564,  0.03077,
                             0.35897,  0.35897,  0.43590,  0.92308,
                            -0.69231, -0.69231, -0.76923, -1.92308);

                assert(inverse(A) == B);
            }

            {
                mat4x4 A;
                MAT4X4_INIT(A,
                             9,  3,  0,  9,
                             7,  5,  6,  1,
                            -6,  0,  9,  6,
                            -3,  0, -9, -4);

                mat4x4 B;
                MAT4X4_INIT(B,
                            -0.04074, -0.07778,  0.14444, -0.22222,
                            -0.07778,  0.03333,  0.36667, -0.33333,
                            -0.02901, -0.14630, -0.10926,  0.12963,
                             0.17778,  0.06667, -0.26667,  0.33333);

                assert(inverse(A) == B);
            }

            {
                mat4x4 A;
                MAT4X4_INIT(A,
                             3, -9,  7,  3,
                             3, -8,  2, -9,
                            -4,  4,  4,  1,
                            -6,  5, -1,  1);

                mat4x4 B;
                MAT4X4_INIT(B,
                             8,  2,  2,  2,
                             3, -1,  7,  0,
                             7,  0,  5,  4,
                             6, -2,  0,  5);

                mat4x4 C = A * B;
                assert(C * inverse(B) == A);
            }
        }
    }
    std::cout << "All tests passed." << std::endl;
    #endif  

}