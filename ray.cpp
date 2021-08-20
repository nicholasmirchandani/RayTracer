#include "ray.h"

ray::ray() : origin(point(0, 0, 0)), direction(vector(0, 0, 1)){

}

ray::ray(const point& p, const vector& v) : origin(p), direction(v) {
    // Just need initializer list :)
}

point position(const ray& r, float t) {
    return r.origin + t * r.direction;
}

int intersect(const ray& r, const sphere& s, intersection* xs, int bufLen) {
    // Assume sphere is of length 1 centered at the origin
    ray r_trans = transform(r, inverse(s.transform));
    vector sphere_to_ray = r_trans.origin - point(0, 0, 0); // Subtracting sphere origin from ray-origin to get the proper vector

    // TODO: Optimizations: dot of a vector with itself is just the magnitude squared
    float temp = magnitude(r_trans.direction);
    float a = temp * temp;
    float b = 2 * dot(r_trans.direction, sphere_to_ray);
    temp = magnitude(sphere_to_ray);
    float c = temp * temp - 1; // mag(sphere_to_ray)^2 - (radius of sphere)^2

    float discriminant = b * b - 4*a*c;

    if(discriminant < 0) {
        return 0;
    // TODO: Figure out if this should be uncommented
    /*} else if (discriminant == 0) {
        xs[0] = 
        return 1;*/
    } else {
        // TODO: Figure out if this needs to be generalized to not just assume 2 (Probably not because the intersection explicitly expects a sphere)
        int count = 2;
        if(count > bufLen) {
            return -1; // ERROR: bufLen is smaller than count, so not all intersects fit.
        }
        xs[0].t = (-b - sqrt(discriminant))/(2 * a);
        xs[0].object = s;
        xs[1].t = (-b + sqrt(discriminant))/(2 * a);
        xs[1].object = s;
        return count;
    }
}

ray transform(const ray& r, const mat4x4& m) {
        ray result(m * r.origin, m * r.direction);
        return result;    
}