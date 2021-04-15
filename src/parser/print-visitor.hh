#pragma once

#include "visitor.hh"
#include "node-f.hh"
#include "node-start.hh"
#include "node-rotate.hh"
#include "node-rule.hh"
#include "node-diameter.hh"
#include "node-leaf.hh"
#include "node-p.hh"
#include "node-back.hh"
#include "scene.hh"
#include <utils/vector3.hh>

class PrintVisitor : public Visitor
{
public:
    PrintVisitor(int depth, std::map<char, Node*>& rules);

    PrintVisitor(const PrintVisitor& obj);

    PrintVisitor& operator=(const PrintVisitor& obj);

    ~PrintVisitor() = default;

    void visit(const Node& node) final;
    void visit(const NodeF& node) final;
    void visit(const NodeStart& node)  final;
    void visit(const NodeRotate& node)  final;
    void visit(const NodeRule& node)  final;
    void visit(const NodeDiameter& node)  final;
    void visit(const NodeLeaf &node) final;
    void visit(const NodeP &node) final;
    void visit(const NodeBack &node) final;

private:
    //To avoid multiple node-start
    bool is_set;

    //Depth for rules (>=0)
    int depth;

    //Set of rules
    std::map<char, Node*> rules;

    Point3 position;
    Vector3 direction;
    //distance
    float t;
    //angle in degree
    float alpha;
};