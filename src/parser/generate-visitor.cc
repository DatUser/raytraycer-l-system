#include "generate-visitor.hh"

GenerateVisitor::GenerateVisitor(Scene* scene, int depth, std::map<char, Node*>& rules,
                                 float diameter_reduction)
: is_set(false),
  scene(scene),
  depth(depth),
  rules(rules),
  position(Point3(0,0,0)),
  direction(Vector3(0,1,0)),
  t(1),
  alpha(90),
  diameter(0.2),
  diameter_reduction(diameter_reduction)
{}

GenerateVisitor::GenerateVisitor(const GenerateVisitor& obj)
{
    is_set = obj.is_set;
    scene = obj.scene;
    depth = obj.depth;
    rules = obj.rules;
    position = obj.position;
    direction = obj.direction;
    t = obj.t;
    alpha = obj.alpha;
    diameter = obj.diameter;
    diameter_reduction = obj.diameter_reduction;
}

GenerateVisitor& GenerateVisitor::operator=(const GenerateVisitor& obj)
{
    is_set = obj.is_set;
    scene = obj.scene;
    depth = obj.depth;
    rules = obj.rules;
    position = obj.position;
    direction = obj.direction;
    t = obj.t;
    alpha = obj.alpha;
    diameter = obj.diameter;
    diameter_reduction = obj.diameter_reduction;

    return *this;
}

void GenerateVisitor::visit(const Node& node)
{
    node.accept(*this);
}

void GenerateVisitor::build_branch(Point3& origin, Point3& dest) const
{
    Color color = Color(0.5,0.3,0.1);
    std::vector<Color> colors = std::vector<Color>();
    colors.push_back(color);
    Texture_Material* texture = new Uniform_Texture(colors, 0.7, 0, 0);
    Cylinder* cylinder = new Cylinder(origin, dest, diameter, texture);
    scene->add_object(cylinder);
}

void GenerateVisitor::visit(const NodeF& node) {
    if (depth == 0){
        Vector3 origin = position;
        position += (direction * t);
        build_branch(origin, position);
    } else {
        depth -=1;
        rules[node.get_rule()]/*->get_children()[0]*/->accept(*this);
        depth += 1;
    }

    GenerateVisitor save = *this;
    /*if (depth == 0)
        t = t * 0.75;*/
    for (unsigned int i = 0; i < node.get_children().size(); i++) {
        node.get_children()[i]->accept(*this);
        if (i != node.get_children().size() - 1)
            *this = save;
    }
}

void GenerateVisitor::visit(const NodeStart& node)
{
    if (!is_set) {
        std::cout << "Setting variables" << std::endl;
        is_set = true;
        position = node.get_origin();
        direction = node.get_direction();
        t = node.get_distance();
        alpha = node.get_angle();
        diameter = node.get_diameter();
    }

    GenerateVisitor save = *this;
    for (unsigned int i = 0; i < node.get_children().size(); i++) {
        node.get_children()[i]->accept(*this);
        if (i != node.get_children().size() - 1)
            *this = save;
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

    GenerateVisitor save = *this;
    for (unsigned int i = 0; i < node.get_children().size(); i++) {
        node.get_children()[i]->accept(*this);
        if (i != node.get_children().size() - 1)
            *this = save;
    }
}

void GenerateVisitor::visit(const NodeRule &node) {
    if (depth != 0){
        depth -=1;
        rules[node.get_rule()]/*->get_children()[0]*/->accept(*this);
        depth += 1;
    }

    GenerateVisitor save = *this;
    for (unsigned int i = 0; i < node.get_children().size(); i++) {
        node.get_children()[i]->accept(*this);
        if (i != node.get_children().size() - 1)
            *this = save;
    }

}

void GenerateVisitor::visit(const NodeDiameter &node) {
    reduce_diameter();

    GenerateVisitor save = *this;
    for (unsigned int i = 0; i < node.get_children().size(); i++) {
        node.get_children()[i]->accept(*this);
        if (i != node.get_children().size() - 1)
            *this = save;
    }
}

void GenerateVisitor::reduce_diameter() {
    diameter *= diameter_reduction;
}
