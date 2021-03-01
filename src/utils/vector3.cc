#include "vector3.hh"

Vector3::Vector3(Point3& a, Point3& b)
{
  x = b.x - a.x;
  y = b.y - a.y;
  z = b.z - a.z;
}

Vector3::Vector3(float x, float y, float z)
: x(x),
  y(y),
  z(z)
{}

Vector3 Vector3::operator*(const float& l) const
{
  return Vector3(x * l, y * l, z *l);
}

Vector3 Vector3::operator-(const Vector3& v) const
{
  return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3 Vector3::operator+(const Vector3& v) const
{
  return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator*(const Vector3& v) const
{
  return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

float Vector3::operator^(const Vector3& v) const
{
  return x * v.x + y * v.y + z *v.z;
}
