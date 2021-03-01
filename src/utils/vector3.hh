#pragma once

#include <iostream>
#include "point3.hh"
#include <math.h>

class Vector3
{
  public:
    Vector3(Point3& a, Point3& b);

    Vector3(float x, float y, float z);

    Vector3 operator*(const float& l) const;

    Vector3 operator-(const Vector3& v) const;

    Vector3 operator+(const Vector3& v) const;

    //Produit vectoriel
    Vector3 operator*(const Vector3& v) const;

    //Produit scalaire
    float operator^(const Vector3& v) const;

  private:
    float x;
    float y;
    float z;
};

std::ostream& operator<<(std::ostream& out, Vector3 &vect);
