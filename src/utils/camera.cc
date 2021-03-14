#include "camera.hh"

Camera::Camera(Point3& center, Point3& target, Vector3& up, float x_angle,
    float y_angle, float z_pos)
: center(center),
  target(target),
  up(up),
  x_angle(x_angle),
  y_angle(y_angle),
  z_pos(z_pos)
{}
