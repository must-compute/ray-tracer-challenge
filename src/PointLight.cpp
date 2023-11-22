#include "PointLight.h"

[[nodiscard]] Color PointLight::intensity() const {
    return intensity_;

}

[[nodiscard]] Tuple PointLight::position() const {
    return position_;
}
