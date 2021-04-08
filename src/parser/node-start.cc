#include "node-start.hh"

NodeStart::NodeStart(Point3& origin, Vector3& direction, float distance)
: origin(origin),
  direction(direction),
  distance(distance)
{
    children = std::vector<Node*>();
}

void NodeStart::accept(Visitor& visitor) const
{
    visitor.visit(*this);
}