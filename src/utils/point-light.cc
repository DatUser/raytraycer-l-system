#include "point-light.hh"

Point_Light::Point_Light(Point3& position, float intensity, uint8_t r,
    uint8_t g, uint8_t b, Vector3& direction)
: Light(position, intensity, r, g, b),
  direction(direction)
{}
