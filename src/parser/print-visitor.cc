#include "print-visitor.hh"

PrintVisitor::PrintVisitor(int depth, std::map<char, Node*>& rules)
: is_set(false),
  depth(depth),
  rules(rules),
  position(Point3(0,0,0)),
  direction(Vector3(0,1,0)),
  t(1),
  alpha(90)
{}

PrintVisitor::PrintVisitor(const PrintVisitor& obj)
{
    is_set = obj.is_set;
    depth = obj.depth;
    rules = obj.rules;
    position = obj.position;
    direction = obj.direction;
    t = obj.t;
    alpha = obj.alpha;
}

PrintVisitor& PrintVisitor::operator=(const PrintVisitor& obj)
{
    is_set = obj.is_set;
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
        std::cout << "F: " << position << std::endl;
        //std::cout << 'F';
    } else {
        depth -= 1;
        rules[node.get_rule()]/*->get_children()[0]*/->accept(*this);
        depth += 1;
    }
    //std::cout << position << std::endl;

    PrintVisitor save = *this;
    for (unsigned int i = 0; i < node.get_children().size(); i++) {
        node.get_children()[i]->accept(*this);
        if (i != node.get_children().size() - 1)
            *this = save;
    }
}

void PrintVisitor::visit(const NodeStart& node)
{
    if (!is_set) {
        std::cout << "Setting variables" << std::endl;
        is_set = true;
        position = node.get_origin();
        direction = node.get_direction();
        t = node.get_distance();
        alpha = node.get_angle();
    }

    PrintVisitor save = *this;
    for (unsigned int i = 0; i < node.get_children().size(); i++) {
        node.get_children()[i]->accept(*this);
        if (i != node.get_children().size() - 1)
            *this = save;
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

    PrintVisitor save = *this;
    for (unsigned int i = 0; i < node.get_children().size(); i++) {
        node.get_children()[i]->accept(*this);
        if (i != node.get_children().size() - 1)
            *this = save;
    }
}

void PrintVisitor::visit(const NodeRule &node) {
    if (depth != 0){
        depth -=1;
        rules[node.get_rule()]/*->get_children()[0]*/->accept(*this);
        depth += 1;
    }

    PrintVisitor save = *this;
    for (unsigned int i = 0; i < node.get_children().size(); i++) {
        node.get_children()[i]->accept(*this);
        if (i != node.get_children().size() - 1)
            *this = save;
    }
}

void PrintVisitor::visit(const NodeDiameter &node) {
    //(void) node;
    //FIXME
    PrintVisitor save = *this;
    for (unsigned int i = 0; i < node.get_children().size(); i++) {
        node.get_children()[i]->accept(*this);
        if (i != node.get_children().size() - 1)
            *this = save;
    }
}
