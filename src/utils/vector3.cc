#include "vector3.hh"

Vector3* Vector3::m_zero = nullptr;

Vector3::Vector3(const Point3& a, const Point3& b)
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
  return Vector3(x * l, y * l, z * l);
}

Vector3 Vector3::operator-(const float& l) const
{
  return Vector3(x - l, y - l, z - l);
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

Vector3 Vector3::get_normalized() const
{
  float norm = sqrt(x * x + y * y + z * z);
  return Vector3(x / norm, y / norm, z / norm);
}

Vector3 Vector3::zero()
{
  if (Vector3::m_zero)
    return *Vector3::m_zero;

  return *(Vector3::m_zero = new Vector3(0, 0, 0));
}
