#pragma once

#include <memory>
#include <optional>
#include "point3.hh"
#include "vector3.hh"
#include "texture-material.hh"

class Object
{
  public:
    virtual std::optional<Point3> intersect(const Point3& p, const Vector3& v)
      const = 0;

    virtual Vector3 get_normal(const Point3& p) const = 0;

    virtual SurfaceInfo get_texture(const Point3& p)
      const = 0;
};
