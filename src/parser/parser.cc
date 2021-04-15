#include "parser.hh"

Parser::Parser(std::string file)
: file(file)
{}

Node* Parser::build_rule(std::string& rule, Point3& origin, Vector3& direction, float distance, float angle, float diameter)
{
    Node* root = new NodeStart(origin, direction, distance, angle, diameter);
    Node* curr = root;
    std::list<Node*> stack = std::list<Node*>();
    std::list<Node*> points_stack = std::list<Node*>();

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
            case '!':
            {
                Node* new_node = new NodeDiameter(0.75);
                curr->add_children(new_node);
                curr = new_node;
                break;
            }
            case '{':
            {
                stack.push_back(curr);
                Node* new_node = new NodeLeaf();
                curr->add_children(new_node);
                curr = new_node;
                break;
            }
            case '}':
            {
                curr = stack.front();
                stack.pop_front();
                break;
            }
            case 'f':
            {
                Node* new_node = new NodeP();
                curr->add_children(new_node);
                curr = new_node;
                break;
            }
            case '|':
            {
                Node* new_node = new NodeBack();
                curr->add_children(new_node);
                curr = new_node;
                break;
            }
            default:
            {
                Node* new_node = new NodeRule(rule[i]);
                curr->add_children(new_node);
                curr = new_node;
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
