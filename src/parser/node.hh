#pragma once

#include <vector>
#include "visitor.hh"
class Visitor;

class Node
{
public:
    virtual ~Node()
    {
        for (auto child : children)
            delete child;
    }

    virtual void accept(Visitor& visitor) const = 0;

    void add_children(Node* node)
    {
        children.push_back(node);
    }

    inline const std::vector<Node*> get_children() const
    {
        return children;
    }

protected:
    std::vector<Node*> children;
};