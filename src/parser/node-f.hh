#pragma once

#include <map>
#include <utils/vector3.hh>
#include "visitor.hh"
#include "node.hh"

class NodeF : public Node
{
public:
    NodeF(char rule);

    void accept(Visitor& visitor) const final;

    inline char get_rule() const
    {
        return rule;
    }


private:
    char rule;

    //THESE ARE USELESS
    //Normalized F direction
    Vector3 direction;
    //Size
    float t;
};