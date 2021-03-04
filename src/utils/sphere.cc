#include "sphere.hh"
#include <memory>
#include <math.h>

Sphere::Sphere(Point3& center, float radius, Texture_Material* texture)
: center(center),
  radius(radius),
  texture(texture)
{}

std::optional<Point3> Sphere::intersect(const Point3& p, const Vector3& v) const
{
  Vector3 q = Vector3(center, p);
  float a = v ^ v;
  float b = v ^ q * 2.0f;
  float c = (q ^ q) - radius * radius;
  float d = b * b - a * c * 4.0f;

  if (d >= 0)
  {
    float t = (-b + sqrt(d))/(2.0f * a);
    return std::optional<Point3>{p + v * t};
  }

  return std::nullopt;
}

Vector3 Sphere::get_normal(const Point3& p) const
{
  //Just need to normalize it  
  return Vector3(center, p).get_normalized();
}

SurfaceInfo Sphere::get_texture(const Point3& p) const
{
  if (p.x == 0)
    return texture->get_point_info(0, 0);
  return texture->get_point_info(0, 0);
}
