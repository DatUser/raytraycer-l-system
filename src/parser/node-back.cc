#include "node-back.hh"


NodeBack::NodeBack()
{
    children = std::vector<Node*>();
}

void NodeBack::accept(Visitor& visitor) const
{
    visitor.visit(*this);
}