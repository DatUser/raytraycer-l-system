#include "node-p.hh"


NodeP::NodeP()
{
    children = std::vector<Node*>();
}

void NodeP::accept(Visitor& visitor) const
{
    visitor.visit(*this);
}