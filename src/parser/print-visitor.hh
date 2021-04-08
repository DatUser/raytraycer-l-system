#pragma once

#include "visitor.hh"
#include "node-f.hh"
#include "node-start.hh"
#include <utils/vector3.hh>

class PrintVisitor : public Visitor
{
public:
    PrintVisitor();

    void visit(const Node& node) final;
    void visit(const NodeF& node) final;
    void visit(const NodeStart& node)  final;

private:
    Point3 position;
    Vector3 direction;
    //distance
    float t;
};