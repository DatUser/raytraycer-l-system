#include "node-rule.hh"

NodeRule::NodeRule(char rule)
: rule(rule)
{
    children = std::vector<Node*>();
}

void NodeRule::accept(Visitor &visitor) const {
    visitor.visit(*this);
}
