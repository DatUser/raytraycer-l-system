#pragma once

#include <utils/vector3.hh>
#include "visitor.hh"
#include "node.hh"

class NodeF : public Node
{
public:
    NodeF();

    NodeF(Vector3& direction, float size);

    void accept(Visitor& visitor) const final;


private:
    //Normalized F direction
    Vector3 direction;
    //Size
    float t;
};