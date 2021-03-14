#pragma once

#include "image.hh"
#include "point3.hh"

class Light
{
  public:

    Light(Point3& position, float intensity, uint8_t r, uint8_t g, uint8_t b)
    : position(position),
      intensity(intensity),
      color((RGB8)aligned_alloc(TL_IMAGE_ALIGNMENT, 3))
    {
      color[0] = r;
      color[1] = g;
      color[2] = b;
    }

    ~Light()
    {
      delete color;
    }

  protected:
    Point3 position;
    float intensity;
    RGB8 color;
};
