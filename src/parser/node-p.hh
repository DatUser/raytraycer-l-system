#pragma once

#include <map>
#include <utils/vector3.hh>
#include "visitor.hh"
#include "node.hh"

//Generates a point
class NodeP : public Node
{
public:
    NodeP();

    void accept(Visitor& visitor) const final;
};