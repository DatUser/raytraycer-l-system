#include "parser.hh"

Parser::Parser(std::string file)
: file(file)
{}

Node* Parser::build_rule(std::string& rule, Point3& origin, Vector3& direction, float distance, float angle)
{
    Node* root = new NodeStart(origin, direction, distance, angle);
    Node* curr = root;
    std::list<Node*> stack = std::list<Node*>();

    for (unsigned int i = 0; i < rule.size(); i++)
    {
        switch (rule[i]) {
            case 'F': {
                Node* new_node = new NodeF('F');
                curr->add_children(new_node);
                curr = new_node;
                break;
            }
            case '+':
            case '-':    
            {
                Node* new_node = new NodeRotate('Z', rule[i] == '+');
                curr->add_children(new_node);
                curr = new_node;
                break;
            }
            case '&':
            case '^':
            {
                Node* new_node = new NodeRotate('X', rule[i] == '&');
                curr->add_children(new_node);
                curr = new_node;
                break;
            }
            case '\\':
            case '/':
            {
                Node* new_node = new NodeRotate('Y', rule[i] == '\\');
                curr->add_children(new_node);
                curr = new_node;
                break;
            }
            case '[':
            {
                stack.push_back(curr);
                break;
            }
            case ']':
            {
                curr = stack.front();
                stack.pop_front();
                break;
            }
        }
    }

    return root;
}

void Parser::parse(std::string sentence, std::map<char, Node*> &rules, Visitor& visitor) {
    for (char c : sentence) {
        rules[c]->accept(visitor);
    }
}
