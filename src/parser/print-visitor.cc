#include "print-visitor.hh"

PrintVisitor::PrintVisitor()
: position(Point3(0,0,0)),
  direction(Vector3(0,1,0)),
  t(1)
{}

void PrintVisitor::visit(const Node& node)
{
    node.accept(*this);
}

void PrintVisitor::visit(const NodeF& node)
{
    std::cout << position << " -> ";
    position += (direction * t);
    std::cout << position << std::endl;
    for (unsigned int i = 0; i < node.get_children().size(); i++) {
        node.get_children()[i]->accept(*this);
    }
}

void PrintVisitor::visit(const NodeStart& node)
{
    std::cout << "Setting variables" << std::endl;
    position = node.get_origin();
    direction = node.get_direction();
    t = node.get_distance();
    for (unsigned int i = 0; i < node.get_children().size(); i++) {
        node.get_children()[i]->accept(*this);
    }

}