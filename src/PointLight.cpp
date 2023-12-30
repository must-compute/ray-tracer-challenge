#include "PointLight.h"

[[nodiscard]] Color PointLight::intensity() const {
  return intensity_;

}

[[nodiscard]] Point PointLight::position() const {
  return position_;
}
