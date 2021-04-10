#pragma once

#include "visitor.hh"

class PrintVisitor : public Visitor
{
public:
    PrintVisitor();

    void visit(const Node& node) const final;
    void visit(const NodeF& node) const final;
};