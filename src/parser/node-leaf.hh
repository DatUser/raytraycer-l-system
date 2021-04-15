#pragma once

#include <utils/vector3.hh>
#include "visitor.hh"
#include "node.hh"

class NodeLeaf : public Node
{
public:
    NodeLeaf();

    void accept(Visitor& visitor) const final;

    inline std::vector<Point3>& get_points()
    {
        return points;
    }

private:
    //Storing the points
    std::vector<Point3> points;
};