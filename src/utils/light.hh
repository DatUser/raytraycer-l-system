#pragma once

#include "image.hh"
#include "point3.hh"

class Light
{
  public:

    Light(Point3& position, float r, float g, float b)
    : position(position),
      //intensity(intensity),
      color({r, g, b})
    {
    }

    const Point3& get_position() const;

    const Color& get_color() const;

    ~Light() = default;

  protected:
    Point3 position;
    //float intensity;
    Color color;
};

#include <light.hxx>