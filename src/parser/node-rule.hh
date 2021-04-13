#pragma once

#include <map>
#include <utils/vector3.hh>
#include "visitor.hh"
#include "node.hh"

class NodeRule : public Node
{
public:
    NodeRule(char rule);

    void accept(Visitor& visitor) const final;

    inline char get_rule() const
    {
        return rule;
    }


private:
    char rule;
};