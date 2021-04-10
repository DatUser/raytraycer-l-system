#pragma once

#include <string>
#include <fstream>
#include "node.hh"

class Parser{
public:
    Parser(std::string file);

    Node* build_rule(std::string& rule);

private:
    std::string file;
};