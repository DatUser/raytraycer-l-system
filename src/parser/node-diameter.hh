#pragma once

#include <map>
#include <utils/vector3.hh>
#include "visitor.hh"
#include "node.hh"

class NodeDiameter : public Node
{
public:
    NodeDiameter(float percent);

    void accept(Visitor& visitor) const final;

    inline char get_percent() const
    {
        return percent;
    }


private:
    //0-1
    float percent;
};