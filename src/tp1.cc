#include <iostream>
#include <iterator>
#include <utils/image.hh>
#include <utils/uniform-texture.hh>
#include <utils/sphere.hh>
#include <utils/cylinder.hh>
#include <utils/camera.hh>
#include <utils/scene.hh>
#include <utils/triangle.hh>
#include <parser/parser.hh>
#include <parser/print-visitor.hh>
#include <parser/generate-visitor.hh>
#include <utils/leaf.hh>
#include <utils/polygon.hh>
#include <utils/ppm-texture.hh>

int main()
{
    //SCENE CREATION
    Image img(1920, 1080);

    Point3 light_pos(5, 15, 0);
    Light light(light_pos, 1, 1, 1);

    Point3 center_cam(0, 20, -50);
    Vector3 up = Vector3(0, 1, 0).get_normalized();
    Point3 target(0, 0, 20);
    Camera camera(center_cam, target, up, 90, 90 * ((float)img.height / (float) img.width), 5);

    Point3 center_s3(5, -2005, 20);
    Color color3{0.8, 0.8, 0.8};
    std::vector<Color> colors_t3;
    colors_t3.push_back(color3);
    std::shared_ptr<Texture_Material> texture3 = std::make_shared<Uniform_Texture>(colors_t3, 0.7, 0.1, 20);
    Sphere s3(center_s3, 2000, texture3);

    Scene scene(camera);


    //LIGHT
    scene.add_light(light);

    //GROUND
    scene.add_object(&s3);

    //PARSING
    Parser parser("");

    //SETTING GRAMMAR RULES
    std::string sentence = "A";
    std::string rule_a = "[&S!A]/////[&S!A]///////[&S!A]";
    std::string rule_s = "FL";
    std::string rule_l = "[^^{-f+f+f-|-f+f+f}]";

    //BUILDING RULE'S TREE
    std::map<char, Node*> rules;
    std::map<char, int> depth;
    int d = 4;//depth

    //ADDING RULES
    Point3 origin = Point3(0,-5,15);
    Vector3 direction = Vector3(0,1,0).get_normalized();
    Node* rule_node_a = parser.build_rule(rule_a, origin, direction, 1, 90, 0.2);
    rules.insert({'A', rule_node_a});
    depth.insert({'A', d});

    Node* rule_node_s = parser.build_rule(rule_s, origin, direction, 1, 90, 0.2);
    rules.insert({'S', rule_node_s});
    depth.insert({'S', d});

    Node* rule_node_l = parser.build_rule(rule_l, origin, direction, 1, 90, 0.2);
    rules.insert({'L', rule_node_l});
    depth.insert({'L', d});

    Node* sentence_node = parser.build_rule(sentence, origin, direction, 5, 22.5, 0.4);
    PrintVisitor printVisitor(1, rules);
    GenerateVisitor generateVisitor(&scene, depth, rules, 0.75);

    //VISITING TREE
    sentence_node->accept(generateVisitor);

    delete rule_node_a;
    delete rule_node_l;
    delete rule_node_s;
    delete sentence_node;

    //RENDENRING SCENE
    std::cout << "Tree is built" << std::endl;
    scene.capture_image(img);

    img.save();
    return 0;
}
