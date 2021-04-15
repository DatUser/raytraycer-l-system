#pragma once

#include <map>
#include <utils/vector3.hh>
#include "visitor.hh"
#include "node.hh"

//Generates a point
class NodeBack : public Node
{
public:
    NodeBack();

    void accept(Visitor& visitor) const final;
};