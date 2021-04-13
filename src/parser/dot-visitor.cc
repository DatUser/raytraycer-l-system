#include "dot-visitor.hh"

DotVisitor::DotVisitor()
: writing_label(true),
  id(0)
{
    std::cout << "digraph G {" << std::endl;
}

DotVisitor::DotVisitor(const DotVisitor& obj)
{
    writing_label = obj.writing_label;
    id = obj.id;
}

DotVisitor& DotVisitor::operator=(const DotVisitor& obj)
{
    writing_label = obj.writing_label;
    id = obj.id;

    return *this;
}

void DotVisitor::visit(const Node& node)
{
    node.accept(*this);
}

void DotVisitor::visit(const NodeF& node)
{
    //std::cout << position << std::endl;

    if (writing_label) {
        std::cout << "    " << id << "   [label = \"" << "F" << "\"]\n";

        for (unsigned int i = 0; i < node.get_children().size(); i++) {
            id += 1;
            node.get_children()[i]->accept(*this);
        }
    } else {
        int node_id = id;

        for (unsigned int i = 0; i < node.get_children().size(); i++) {
            id += 1;
            std::cout << "    " << node_id << " -> " << id << ";\n";
            node.get_children()[i]->accept(*this);
        }
    }
}

void DotVisitor::visit(const NodeStart& node)
{
    std::cout << "---Generating dot---" << std::endl;
    std::cout << "    " << id << "   [label = \"" << "Start" << "\"]\n";

    //LABEL generation
    for (unsigned int i = 0; i < node.get_children().size(); i++) {
        id += 1;
        node.get_children()[i]->accept(*this);
    }

    //Tree generation
    writing_label = false;
    int node_id = id;
    for (unsigned int i = 0; i < node.get_children().size(); i++) {
        std::cout << "    " << node_id << " -> " << id << ";\n";
        id += 1;
        node.get_children()[i]->accept(*this);
    }
}

void DotVisitor::visit(const NodeRotate &node)
{
    switch (node.get_axis())
    {
        case 'X':
            std::cout << (node.get_positive());
            //std::cout << ((node.get_positive()) ? '&' : '^');
            break;
        case 'Y':
            std::cout << (node.get_positive());
            //std::cout << ((node.get_positive()) ? '\\' : '/');
            break;
        case 'Z':
            std::cout << (node.get_positive());
            //std::cout << ((node.get_positive()) ? '+' : '-');
            break;
    }

    DotVisitor save = *this;
    for (unsigned int i = 0; i < node.get_children().size(); i++) {
        node.get_children()[i]->accept(*this);
        if (i != node.get_children().size() - 1)
            *this = save;
    }
}

void DotVisitor::visit(const NodeRule &node) {
    DotVisitor save = *this;
    for (unsigned int i = 0; i < node.get_children().size(); i++) {
        node.get_children()[i]->accept(*this);
        if (i != node.get_children().size() - 1)
            *this = save;
    }
}

void DotVisitor::visit(const NodeDiameter &node) {
    //(void) node;
    //FIXME
    DotVisitor save = *this;
    for (unsigned int i = 0; i < node.get_children().size(); i++) {
        node.get_children()[i]->accept(*this);
        if (i != node.get_children().size() - 1)
            *this = save;
    }
}
