#include "node-f.hh"


NodeF::NodeF(char rule)
: rule(rule),
  direction(Vector3(0,0,1)),
  t(1)
{
    children = std::vector<Node*>();
}

void NodeF::accept(Visitor& visitor) const
{
    visitor.visit(*this);
}