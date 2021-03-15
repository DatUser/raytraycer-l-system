#pragma once

#include <iostream>
#include <math.h>
#include "point3.hh"

class Point3;

class Vector3
{
  public:
    Vector3(const Point3& a, const Point3& b);

    Vector3(float x, float y, float z);

    Vector3 operator*(const float& l) const;

    Vector3 operator-(const float& l) const;

    Vector3 operator-(const Vector3& v) const;

    Vector3 operator+(const Vector3& v) const;

    //Produit vectoriel
    Vector3 operator*(const Vector3& v) const;

    //Produit scalaire
    float operator^(const Vector3& v) const;

    Vector3 get_normalized() const;

    void normalize();

    static Vector3 zero();

    float x;
    float y;
    float z;

    float norm;

  private:
    static Vector3* m_zero;
};

std::ostream& operator<<(std::ostream& out, Vector3 &vect);

float operator^(const Vector3& v, const Point3& p);

float norm(const Vector3& a, const Vector3& b);
