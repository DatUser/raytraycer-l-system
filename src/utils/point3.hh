/*#pragma once

#include <fstream>
#include <ostream>
#include "vector3.hh"

class Vector3;

class Point3
{
  public:

    Point3(float x, float y, float z);

    Point3 operator*(const float& l) const;

    Point3 operator-(const Point3& p) const;

    Point3 operator+(const Vector3& v) const;

    bool operator==(const Point3& p) const;

    float x;
    float y;
    float z;
};

std::ostream& operator<<(std::ostream& out, Point3 &p);

float norm(const Point3& a, const Point3& b);

float norm(const Point3& a, const Vector3& b);
*/