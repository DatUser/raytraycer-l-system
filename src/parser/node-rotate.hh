#pragma once

#include "node.hh"
#include "visitor.hh"

class NodeRotate : public Node
{
public:
    NodeRotate(char axis, bool positive);

    void accept(Visitor& visitor) const final;

    inline char get_axis() const
    {
        return axis;
    }

    inline bool get_positive() const
    {
        return positive;
    }

private:
    // 'X', 'Y', 'Z'
    char axis;
    bool positive;
};