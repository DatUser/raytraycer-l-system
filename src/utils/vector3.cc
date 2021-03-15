#include "vector3.hh"
#include <ostream>

Vector3* Vector3::m_zero = nullptr;

Vector3::Vector3(const Point3& a, const Point3& b)
{
  x = b.x - a.x;
  y = b.y - a.y;
  z = b.z - a.z;
  norm = sqrt(x * x + y * y + z * z);
}

Vector3::Vector3(float x, float y, float z)
: x(x),
  y(y),
  z(z),
  norm(sqrt(x * x + y * y + z * z))
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

void Vector3::normalize()
{
  float norm = sqrt(x * x + y * y + z * z);
  x /= norm;
  y /= norm;
  z /= norm;

  norm = 1;
}

Vector3 Vector3::zero()
{
  if (Vector3::m_zero)
    return *Vector3::m_zero;

  return *(Vector3::m_zero = new Vector3(0, 0, 0));
}

std::ostream& operator<<(std::ostream& out, Vector3& vect)
{
  return out << "(" << vect.x << ", " << vect.y << ", " << vect.z << ")";
}

float operator^(const Vector3& v, const Point3& p)
{
    return v.x * p.x + v.y * p.y + v.z * p.z;
}

float norm(const Vector3& a, const Vector3& b)
{
  float vx = b.x - a.x;
  float vy = b.y - a.y;
  float vz = b.z - a.z;
  return sqrt(vx * vx + vy * vy + vz * vz);
}
