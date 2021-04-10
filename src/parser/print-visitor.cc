#include "print-visitor.hh"

PrintVisitor::PrintVisitor()
{}

void PrintVisitor::visit(const Node &node) const
{
    node.accept(*this);
}

void PrintVisitor::visit(const NodeF &node) const
{
    node.accept(*this);
}