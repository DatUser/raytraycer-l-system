#include "sphere.hh"
#include <memory>
#include <math.h>

Sphere::Sphere(Point3& center, float radius, Texture_Material* texture)
: center(center),
  radius(radius),
  texture(texture)
{}

std::optional<Vector3> Sphere::intersect(const Vector3& origin,
    const Vector3& direction) const
{
  Vector3 q(origin.x - center.x, origin.y - center.y, origin.z - center.z);
  float a = dotProd(direction, direction);
  float b = dotProd(direction, q) * 2;
  float c = (dotProd(q, q)) - radius * radius;
  float d = b * b - a * c * 4.0f;

  if (d >= 0)
  {
    float t = (-b + sqrt(d))/(2.0f * a);
    return std::optional<Vector3>{origin + (direction * t)};
  }

  return std::nullopt;
}

Vector3 Sphere::get_normal(const Point3& p) const
{
  //Just need to normalize it  
  return Vector3(center, p).get_normalized();
}

SurfaceInfo Sphere::get_texture(const Vector3& p) const
{
  if (p.x == 0)
    return texture->get_point_info(0, 0);
  return texture->get_point_info(0, 0);
}
