#pragma once

#include <list>
#include <string>
#include <fstream>
#include "node.hh"
#include "node-f.hh"
#include "node-start.hh"
#include "node-rotate.hh"

class Parser{
public:
    Parser(std::string file);

    Node* build_rule(std::string& rule, Point3& origin, Vector3& direction, float distance, float angle);

    void parse(std::string sentence, std::map<char, Node*>& rules, Visitor& visitor);

private:
    std::string file;
};