#include "node-diameter.hh"

NodeDiameter::NodeDiameter(float percent)
: percent(percent)
{
    children = std::vector<Node*>();
}

void NodeDiameter::accept(Visitor &visitor) const {
    visitor.visit(*this);
}
