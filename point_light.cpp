#include "point_light.h"

point_light::point_light(point p, color c) : intensity(c), position(p) {
    // Initializer List is all we need
}

color lighting(material m, point_light light, point position, vector eyev, vector normalv) {
    color effective_color = m.col * light.intensity;
    vector lightv = normalize(light.position - position);
    color ambient = effective_color * m.ambient;

    float light_dot_normal = dot(lightv, normalv);
    color black(0, 0, 0);
    color diffuse;
    color specular;
    if (light_dot_normal < 0) {
        diffuse = black;
        specular = black;
    } else {
        diffuse = effective_color * m.diffuse * light_dot_normal;
        vector reflectv = reflect(-lightv, normalv);
        float reflect_dot_eye = dot(reflectv, eyev);
        if(reflect_dot_eye <= 0) {
            specular = black;
        } else {
            float factor = pow(reflect_dot_eye, m.shininess);
            static float maxFactor = factor;
            specular = light.intensity * m.specular * factor;
        }
    }

    return ambient + diffuse + specular;
}