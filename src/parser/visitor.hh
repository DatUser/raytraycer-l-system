#pragma once

/*#include "node.hh"
#include "node-f.hh"
#include "node-start.hh"*/

class Node;
class NodeF;
class NodeStart;
class NodeRotate;
class NodeRule;
class NodeDiameter;
class NodeLeaf;
class NodeP;
class NodeBack;

class Visitor
{
public:
    virtual void visit(const Node& node)  = 0;
    virtual void visit(const NodeF& node)  = 0;
    virtual void visit(const NodeStart& node)  = 0;
    virtual void visit(const NodeRotate& node)  = 0;
    virtual void visit(const NodeRule& node)  = 0;
    virtual void visit(const NodeDiameter& node)  = 0;
    virtual void visit(const NodeLeaf& node) = 0;
    virtual void visit(const NodeP& node) = 0;
    virtual void visit(const NodeBack& node) = 0;
};