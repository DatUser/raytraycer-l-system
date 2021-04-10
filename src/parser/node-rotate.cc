#include "node-rotate.hh"

NodeRotate::NodeRotate(char axis, bool positive)
: axis(axis),
  positive(positive)
{
    children = std::vector<Node*>();
}

void NodeRotate::accept(Visitor &visitor) const
{
    visitor.visit(*this);
}