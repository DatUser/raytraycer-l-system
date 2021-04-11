#include "print-visitor.hh"

PrintVisitor::PrintVisitor(int depth, std::map<char, Node*>& rules)
: depth(depth),
  rules(rules),
  position(Point3(0,0,0)),
  direction(Vector3(0,1,0)),
  t(1),
  alpha(90)
{}

PrintVisitor::PrintVisitor(const PrintVisitor& obj)
{
    depth = obj.depth;
    rules = obj.rules;
    position = obj.position;
    direction = obj.direction;
    t = obj.t;
    alpha = obj.alpha;
}

PrintVisitor& PrintVisitor::operator=(const PrintVisitor& obj)
{
    depth = obj.depth;
    rules = obj.rules;
    position = obj.position;
    direction = obj.direction;
    t = obj.t;
    alpha = obj.alpha;

    return *this;
}

void PrintVisitor::visit(const Node& node)
{
    node.accept(*this);
}

void PrintVisitor::visit(const NodeF& node)
{
    if (depth == 0) {
        //std::cout << position << " -> ";
        position += (direction * t);
        std::cout << position << std::endl;
        //std::cout << 'F';
    } else {
        depth -= 1;
        rules[node.get_rule()]->get_children()[0]->accept(*this);
        depth += 1;
    }
    //std::cout << position << std::endl;

    //PrintVisitor save = *this;
    for (unsigned int i = 0; i < node.get_children().size(); i++) {
        node.get_children()[i]->accept(*this);
        //*this = save;
    }
}

void PrintVisitor::visit(const NodeStart& node)
{
    std::cout << "Setting variables" << std::endl;
    position = node.get_origin();
    direction = node.get_direction();
    t = node.get_distance();
    alpha = node.get_angle();
    //This should have a single child so there's no need to make a save
    for (unsigned int i = 0; i < node.get_children().size(); i++) {
        node.get_children()[i]->accept(*this);
    }

}

void PrintVisitor::visit(const NodeRotate &node)
{

    std::cout << "Rotating: " << direction << " -> ";
    switch (node.get_axis())
    {
        case 'X':
            rotateAroundX(direction, (node.get_positive()) ? alpha : -alpha);
            //std::cout << ((node.get_positive()) ? '&' : '^');
            break;
        case 'Y':
            rotateAroundY(direction, (node.get_positive()) ? alpha : -alpha);
            //std::cout << ((node.get_positive()) ? '\\' : '/');
            break;
        case 'Z':
            rotateAroundZ(direction, (node.get_positive()) ? alpha : -alpha);
            //std::cout << ((node.get_positive()) ? '+' : '-');
            break;
    }
    std::cout << direction << std::endl;

    //PrintVisitor save = *this;
    for (unsigned int i = 0; i < node.get_children().size(); i++) {
        node.get_children()[i]->accept(*this);
        //*this = save;
    }
}