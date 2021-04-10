#pragma once

#include "node.hh"
#include <utils/vector3.hh>

class Node;

class NodeF : public Node
{
public:
    NodeF();

    NodeF(Vector3& direction, float size);

private:
    //Normalized F direction
    Vector3 direction;
    //Size
    float t;
};