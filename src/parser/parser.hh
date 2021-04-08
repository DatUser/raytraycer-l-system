#pragma once

#include <string>
#include <fstream>
#include "node.hh"
#include "node-f.hh"
#include "node-start.hh"

class Parser{
public:
    Parser(std::string file);

    Node* build_rule(std::string& rule, Point3& origin, Vector3& direction, float distance);

private:
    std::string file;
};