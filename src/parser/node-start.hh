#pragma once

#include "visitor.hh"
#include "node.hh"
#include "vector3.hh"

//This class will always be the root of the tree
//and will contain information tree generation
class NodeStart : public Node {
public:
    NodeStart(Point3& origin, Vector3& direction, float distance, float angle, float diameter);

    void accept(Visitor& visitor) const final;

    inline Point3 get_origin() const
    {
        return origin;
    }

    inline Point3 get_direction() const
    {
        return direction;
    }

    inline float get_distance() const
    {
        return distance;
    }

    inline float get_angle() const
    {
        return angle;
    }

    inline float get_diameter() const
    {
        return diameter;
    }

private:
    Point3 origin;
    Vector3 direction;
    float distance;
    float angle;
    float diameter;
};