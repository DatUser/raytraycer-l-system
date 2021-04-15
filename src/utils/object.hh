#pragma once

#include <memory>
#include <optional>
#include "vector3.hh"
#include "texture-material.hh"

class Object
{
  public:
    virtual std::optional<Vector3> intersect(const Vector3& p, const Vector3& v)
      const = 0;

    virtual Vector3 get_normal(const Point3& p) const = 0;

    virtual SurfaceInfo get_texture(const Vector3& p)
      const = 0;
};
