#pragma once

/*#include "node.hh"
#include "node-f.hh"
#include "node-start.hh"*/

class Node;
class NodeF;
class NodeStart;
class NodeRotate;

class Visitor
{
public:
    virtual void visit(const Node& node)  = 0;
    virtual void visit(const NodeF& node)  = 0;
    virtual void visit(const NodeStart& node)  = 0;
    virtual void visit(const NodeRotate& node)  = 0;
};