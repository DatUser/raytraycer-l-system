#pragma once

#include "node.hh"
#include "node-f.hh"

class Visitor
{
public:
    virtual void visit(const Node& node) const = 0;
    virtual void visit(const NodeF& node) const = 0;
};