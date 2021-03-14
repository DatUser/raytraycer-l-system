#pragma once

#include <memory>
#include "object.hh"

class Sphere : public Object
{
  public:
    Sphere(Point3& center, float radius, Texture_Material* texture);

    std::optional<Vector3> intersect(const Vector3& p, const Vector3& v) const
      final;

    Vector3 get_normal(const Point3& p) const final;

    SurfaceInfo get_texture(const Vector3& p) const final;

  private:
    Point3 center;
    float radius;
    std::shared_ptr<Texture_Material> texture;
};
