#include "node-start.hh"

NodeStart::NodeStart(Point3& origin, Vector3& direction, float distance, float angle, float diameter)
: origin(origin),
  direction(direction),
  distance(distance),
  angle(angle),
  diameter(diameter)
{
    children = std::vector<Node*>();
}

void NodeStart::accept(Visitor& visitor) const
{
    visitor.visit(*this);
}