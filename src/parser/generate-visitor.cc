#include "generate-visitor.hh"

GenerateVisitor::GenerateVisitor(Scene* scene, int depth, std::map<char, Node*>& rules)
: scene(scene),
  depth(depth),
  rules(rules),
  position(Point3(0,0,0)),
  direction(Vector3(0,1,0)),
  t(1),
  alpha(90)
{}

GenerateVisitor::GenerateVisitor(const GenerateVisitor& obj)
{
    scene = obj.scene;
    depth = obj.depth;
    rules = obj.rules;
    position = obj.position;
    direction = obj.direction;
    t = obj.t;
    alpha = obj.alpha;
}

GenerateVisitor& GenerateVisitor::operator=(const GenerateVisitor& obj)
{
    scene = obj.scene;
    depth = obj.depth;
    rules = obj.rules;
    position = obj.position;
    direction = obj.direction;
    t = obj.t;
    alpha = obj.alpha;

    return *this;
}

void GenerateVisitor::visit(const Node& node)
{
    node.accept(*this);
}

void GenerateVisitor::build_branch(Point3& origin, Point3& dest) const
{
    Color color = Color(0,1,0);
    std::vector<Color> colors = std::vector<Color>();
    colors.push_back(color);
    Texture_Material* texture = new Uniform_Texture(colors, 1, 1, 10);
    Cylinder* cylinder = new Cylinder(origin, dest, 0.1, texture);
    scene->add_object(cylinder);
}

void GenerateVisitor::visit(const NodeF& node) {
    if (depth == 0){
        Vector3 origin = position;
        position += (direction * t);
        build_branch(origin, position);
    } else {
        depth -=1;
        rules[node.get_rule()]->get_children()[0]->accept(*this);
        depth += 1;
    }

    //GenerateVisitor save = *this;
    for (unsigned int i = 0; i < node.get_children().size(); i++) {
        node.get_children()[i]->accept(*this);
        //*this = save;
    }
}

void GenerateVisitor::visit(const NodeStart& node)
{
    std::cout << "Setting variables" << std::endl;
    position = node.get_origin();
    direction = node.get_direction();
    t = node.get_distance();
    alpha = node.get_angle();
    //This should have a single child so there's no need to make a save
    for (unsigned int i = 0; i < node.get_children().size(); i++) {
        node.get_children()[i]->accept(*this);
    }

}

void GenerateVisitor::visit(const NodeRotate &node)
{
    switch (node.get_axis())
    {
        case 'X':
            rotateAroundX(direction, (node.get_positive()) ? alpha : -alpha);
            break;
        case 'Y':
            rotateAroundY(direction, (node.get_positive()) ? alpha : -alpha);
            break;
        case 'Z':
            rotateAroundZ(direction, (node.get_positive()) ? alpha : -alpha);
            break;
    }

    //GenerateVisitor save = *this;
    for (unsigned int i = 0; i < node.get_children().size(); i++) {
        node.get_children()[i]->accept(*this);
        //*this = save;
    }
}