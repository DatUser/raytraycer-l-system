#include "node-f.hh"


NodeF::NodeF()
: direction(Vector3(0,0,1)),
  t(1)
{
}

NodeF::NodeF(Vector3& direction, float size)
: direction(direction),
  t(size)
{}