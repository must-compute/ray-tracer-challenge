#include "Material.h"

Material::Material() : color{make_color(1.0, 1.0, 1.0)}, ambient{0.1}, diffuse{0.9}, specular{0.9},
                       shininess{200.0} {}
