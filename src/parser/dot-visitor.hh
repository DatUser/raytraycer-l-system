#pragma once

#include "visitor.hh"
#include "node-f.hh"
#include "node-start.hh"
#include "node-rotate.hh"
#include "node-rule.hh"
#include "node-diameter.hh"
#include "scene.hh"
#include <utils/vector3.hh>

class DotVisitor : public Visitor
{
public:
    DotVisitor();

    DotVisitor(const DotVisitor& obj);

    DotVisitor& operator=(const DotVisitor& obj);

    ~DotVisitor() = default;

    void visit(const Node& node) final;
    void visit(const NodeF& node) final;
    void visit(const NodeStart& node)  final;
    void visit(const NodeRotate& node)  final;
    void visit(const NodeRule& node)  final;
    void visit(const NodeDiameter& node)  final;

private:
    bool writing_label;

    //Stores node's id
    int id;

};