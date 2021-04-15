#include "node-leaf.hh"

NodeLeaf::NodeLeaf()
: points(std::vector<Point3>())
{
    children = std::vector<Node*>();
}

void NodeLeaf::accept(Visitor &visitor) const {
    visitor.visit(*this);
}

