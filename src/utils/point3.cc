#include "point3.hh"
#include <ostream>

Point3::Point3(float _x, float _y, float _z)
: x(_x),
  y(_y),
  z(_z)
{}

Point3 Point3::operator*(const float& l) const
{
  return Point3(x * l, y * l, z * l); 
}

Point3 Point3::operator-(const Point3& p) const
{
  return Point3(x - p.x, y - p.y, z - p.z);
}

Point3 Point3::operator+(const Vector3& v) const
{
  return Point3(x + v.x, y + v.y, z + v.z);
}

bool Point3::operator==(const Point3& p) const
{
  return x == p.x && y == p.y && z == p.z;
}

std::ostream& operator<<(std::ostream& out, Point3 &p)
{
    return out << "(" << p.x << ", " << p.y << ", " << p.z << ")";
}
