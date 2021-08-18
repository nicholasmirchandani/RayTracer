#define RUN_TESTS

#include <iostream>
#include <fstream>
#include <cassert>
#include "tuple.h"
#include "point.h"
#include "vector.h"
#include "color.h"
#include "canvas.h"

void tick(tuple& projPos, tuple& projVel, tuple gravity, tuple wind);

int main() {

    #ifdef RUN_TESTS
    { // Chapter 1: Tuples, Points, and Vectors
        { // Test 1: constructing a tuple functions properly.  w = 1.0f means it's a point, w = 0.0f means it's a vector
            // Doing float comparison using epsilon as defined in tuple.h
            tuple a(4.3, -4.2, 3.1, 1.0);
            bool xEq = abs(a.x - 4.3) < EPSILON;
            bool yEq = abs(a.y - -4.2) < EPSILON;
            bool zEq = abs(a.z - 3.1) < EPSILON;
            bool wEq = abs(a.w - 1.0) < EPSILON;
            assert(xEq && yEq && zEq && wEq);
            assert(a.isPoint());

            tuple b(4.3, -4.2, 3.1, 0.0);
            xEq = abs(b.x - 4.3) < EPSILON;
            yEq = abs(b.y - -4.2) < EPSILON;
            zEq = abs(b.z - 3.1) < EPSILON;
            wEq = abs(b.w - 0.0) < EPSILON;
            assert(xEq && yEq && zEq && wEq);
            assert(!b.isPoint());
        }
        
        { // Test 2: Point and vector shorthands as tuple 
            point p(4, -4, 3);
            assert(p == tuple(4, -4, 3, 1));
            assert(p.isPoint());
            vector v(4, -4, 3);
            assert(v == tuple(4, -4, 3, 0));
            assert(!v.isPoint());
        }

        { // Test 3: Tuple Arithmetic: Addition, subtraction, negation, and scalar multiplication
            tuple a1(3, -2, 5, 1);
            tuple a2(-2, 3, 1, 0);
            assert(a1 + a2 == tuple(1, 1, 6, 1));

            point p1(3, 2, 1);
            point p2(5, 6, 7);
            assert(p1 - p2 == vector(-2, -4, -6));

            point p(3, 2, 1);
            vector v(5, 6, 7);
            assert(p - v == point(-2, -4, -6));

            vector v1(3, 2, 1);
            vector v2(5, 6, 7);
            assert(v1 - v2 == vector(-2, -4, -6));

            tuple a(1, -2, 3, -4);
            assert(-a == tuple(-1, 2, -3, 4));
            assert(a * 3.5f == tuple(3.5, -7, 10.5, -14));
            assert(3.5f * a == tuple(3.5, -7, 10.5, -14)); // Commutativity test for scalar multiplication
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
            // Doing float comparison using epsilon as defined in tuple.h
            bool rEq = abs(c.r - -0.5) < EPSILON;
            bool gEq = abs(c.g - 0.4) < EPSILON;
            bool bEq = abs(c.b - 1.7) < EPSILON;
            bool aEq = abs(c.a - 1.0) < EPSILON;
            assert(rEq && gEq && bEq && aEq);

            c = color(-0.5, 0.4, 1.7, 0.7f);
            rEq = abs(c.r - -0.5) < EPSILON;
            gEq = abs(c.g - 0.4) < EPSILON;
            bEq = abs(c.b - 1.7) < EPSILON;
            aEq = abs(c.a - 0.7f) < EPSILON;
            assert(rEq && gEq && bEq && aEq);
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
            std::cout << "PPM Text: \n" << c.ToPPM() << std::endl;
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
    std::cout << "All tests passed." << std::endl;
    #endif  

    // End of Chapter 2: Projectile visualization
    point projPos(0, 1, 0);
    tuple projVel = normalize(vector(1, 1.8, 0)) * 11.25f;
    vector gravity(0, -0.1, 0);
    vector wind(-0.01, 0, 0);
    canvas c(900, 550);
    
    color red(1, 0, 0);
    while(projPos.y >= 1) {
        c[(int)(projPos.x + 0.5f)][550 - (int)(projPos.y + 0.5f)] = red;
        tick(projPos, projVel, gravity, wind);
    }

    std::ofstream os;
    os.open("Proj.ppm");
    c.writePPM(os); // NOTE: Use writePPM instead of ToPPM for speed, especially for larger file sizes :)
    os.close();
    std::cout << "Done :)" << std::endl;
}

void tick(tuple& projPos, tuple& projVel, tuple gravity, tuple wind) {
    projPos = (projPos + projVel);
    projVel = (projVel + gravity + wind);
}