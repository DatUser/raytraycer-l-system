#pragma once

#include "visitor.hh"
#include "node-f.hh"
#include "node-start.hh"
#include "node-rotate.hh"
#include "scene.hh"
#include <utils/vector3.hh>

class PrintVisitor : public Visitor
{
public:
    PrintVisitor();

    PrintVisitor(const PrintVisitor&);

    PrintVisitor& operator=(const PrintVisitor&);

    ~PrintVisitor() = default;

    void visit(const Node& node) final;
    void visit(const NodeF& node) final;
    void visit(const NodeStart& node)  final;
    void visit(const NodeRotate& node)  final;

private:
    Point3 position;
    Vector3 direction;
    //distance
    float t;
    //angle in degree
    float alpha;
};