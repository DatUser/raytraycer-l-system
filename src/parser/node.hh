#pragma once

#include <vector>
class Visitor;

class Node
{
public:
    virtual void accept(const Visitor& visitor) const = 0;

protected:
    std::vector<Node*> childrens;

};