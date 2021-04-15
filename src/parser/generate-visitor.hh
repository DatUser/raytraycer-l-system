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
#include <utils/cylinder.hh>
#include <utils/polygon.hh>
#include <utils/uniform-texture.hh>
#include <utils/vector3.hh>

class GenerateVisitor : public Visitor
{
public:
    GenerateVisitor(Scene* scene, std::map<char, int>& depth, std::map<char, Node*>& rules
                    , float diameter_reduction);

    GenerateVisitor(const GenerateVisitor& obj);

    GenerateVisitor& operator=(const GenerateVisitor& obj);

    ~GenerateVisitor() = default;

    void visit(const Node& node) final;
    void visit(const NodeF& node) final;
    void visit(const NodeStart& node)  final;
    void visit(const NodeRotate& node)  final;
    void visit(const NodeRule& node)  final;
    void visit(const NodeDiameter& node)  final;
    void visit(const NodeLeaf& node)  final;
    void visit(const NodeP& node)  final;
    void visit(const NodeBack& node)  final;

    void reduce_diameter();

private:
    void build_branch(Point3& origin, Point3& dest) const;
    void build_polygon() const;

    //To avoid multiple node-start
    bool is_set;

    //Current scene
    Scene* scene;

    //Depth for rules (>=0)
    std::map<char, int> depth;
    //int depth;

    //Set of rules
    std::map<char, Node*> rules;

    Point3 position;
    Vector3 direction;
    //distance
    float t;
    //angle in degree
    float alpha;

    float diameter;
    float diameter_reduction;

    //points for polygon
    std::vector<Point3> points;
};