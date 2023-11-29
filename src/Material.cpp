#include "Material.h"

Material::Material() : color{make_color(1.0, 1.0, 1.0)}, ambient{0.1}, diffuse{0.9}, specular{0.9},
                       shininess{200.0}, reflective{0.0} {}

Color Material::lighting(const Shape &object, const PointLight &light, const Tuple &point, const Tuple &eyev,
                         const Tuple &normalv,
                         const bool in_shadow) const {
    const auto color_to_use = pattern ? pattern->pattern_at_shape(object, point) : color;

    const auto effective_color = color_to_use * light.intensity();
    const auto lightv = (light.position() - point).normalize();
    const auto ambient_contribution = effective_color * ambient;

    if (in_shadow) {
        return ambient_contribution;
    }

    const auto light_dot_normal = lightv.dot(normalv);
    const auto black = make_color(0.0, 0.0, 0.0);
    Color diffuse_contribution{};
    Color specular_contribution{};
    if (light_dot_normal < 0) {
        // the light is on the other side of the surface, therefore diffuse and specular do not contribute
        diffuse_contribution = black;
        specular_contribution = black;

    } else {
        diffuse_contribution = effective_color * diffuse * light_dot_normal;
        const auto reflectv = (-lightv).reflect(normalv);
        const auto reflect_dot_eye = reflectv.dot(eyev);
        if (reflect_dot_eye <= 0) {
            // the light reflects away from the eye, so specular does not contribute
            specular_contribution = black;
        } else {
            const auto factor = std::pow(reflect_dot_eye, shininess);
            specular_contribution = light.intensity() * specular * factor;
        }
    }

    return ambient_contribution + diffuse_contribution + specular_contribution;
}
