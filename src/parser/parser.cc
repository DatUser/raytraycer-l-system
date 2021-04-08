#include "parser.hh"

Parser::Parser(std::string file)
: file(file)
{}

Node* Parser::build_rule(std::string& rule, Point3& origin, Vector3& direction, float distance)
{
    Node* root = new NodeStart(origin, direction, distance);
    Node* curr = root;

    for (unsigned int i = 0; i < rule.size(); i++)
    {
        switch (rule[i]) {
            case 'F':
                Node* new_node = new NodeF();
                curr->add_children(new_node);
                curr = new_node;
                break;
        }
    }

    return root;
}