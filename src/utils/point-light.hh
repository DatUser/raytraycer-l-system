#pragma once

#include "light.hh"
#include "vector3.hh"

class Point_Light : Light
{
  public:

    Point_Light(Point3& position, float intensity, uint8_t r, uint8_t g,
	uint8_t b, Vector3& direction);

    ~Point_Light();

  private:
    Vector3 direction;
};
