#pragma once

#include <fstream>
#include <ostream>

class Point3
{
    Point3(float x, float y, float z);

    Point3 operator*(const float &l) const;

    public:
        float x;
        float y;
        float z;
};

std::ostream& operator<<(std::ostream& out, Point3 &p);
