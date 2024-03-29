#pragma once

#include "vector3.hh"
#include "image.hh"
#include <math.h>

class Camera
{
  public:
    Camera(Point3& center, Point3& target, Vector3& up, float x_angle,
	float y_angle, float z_pos);


  //private:
    Point3 center;
    Point3 target;
    Vector3 up;
    float x_angle;
    float y_angle;
    float z_pos;

    Vector3 y;
    Vector3 z;
    Vector3 x;
};
