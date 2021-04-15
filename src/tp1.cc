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

    Point3 center_cam(0, 0, -50);
    Vector3 up = Vector3(0, 1, 0).get_normalized();
    Point3 target(0, 0, 20);
    Camera camera(center_cam, target, up, 90, 90 * ((float)img.height / (float) img.width), 5);

    Point3 center_s3(5, -2005, 20);
    //Color color2{0.1,0.71,0.1};
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
    Parser parser("test");

    //SETTING GRAMMAR RULES
    /*std::string sentence = "F-F-F-F";
    std::string rule = "F-F+F+FF-F-F+F";*/
    //std::string rule = "F[+F][-F][&F][^F]";
    std::string sentence = "A";
    std::string rule_a = "[&F!A]/////[&F!A]///////[&F!A]";
    std::string rule_f = "S/////F";
    std::string rule_s = "FL";
    std::string rule_l = "[^^{-f+f+f-|-f+f+f}]";

    //BUILDING RULE'S TREE
    std::map<char, Node*> rules;
    std::map<char, int> depth;
    int d = 1;//depth

    Point3 origin = Point3(0,-5,15);
    Vector3 direction = Vector3(0,1,1).get_normalized();
    Node* rule_node_a = parser.build_rule(rule_a, origin, direction, 1, 90, 0.2);
    rules.insert({'A', rule_node_a});
    depth.insert({'A', d});

    Node* rule_node_f = parser.build_rule(rule_f, origin, direction, 1, 90, 0.2);
    rules.insert({'F', rule_node_f});
    depth.insert({'F', d});

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
    //sentence_node->accept(printVisitor);
    //rule_node->accept(generateVisitor);
    //parser.parse(sentence, rules, printVisitor);

    //TRYING TO DISPLAY A POLYGON
    /*Point3 pol2(2, 1, 12);
    Point3 pol3(1, 2, 12);
    Point3 pol4(-1, 2, 12);
    Point3 pol5(-2, 1, 12);
    Point3 pol6(-1, 0, 12);

    std::vector<Point3> pol_pts;
    pol_pts.push_back(pol6);
    pol_pts.push_back(pol5);
    pol_pts.push_back(pol4);
    pol_pts.push_back(pol3);
    pol_pts.push_back(pol2);
    pol_pts.push_back(pol1);

    Color color_l{0.2, 0.8, 0.1};
    std::vector<Color> colors_l;
    colors_l.push_back(color_l);
    std::shared_ptr<Texture_Material> texture_l = std::make_shared<Uniform_Texture>(colors_l, 0.7, 0.1, 20);
    Polygon p = Polygon(pol_pts, texture_l);
    scene.add_object(&p);*/

    delete rule_node_a;
    delete rule_node_f;
    delete rule_node_s;
    delete sentence_node;

    //RENDENRING SCENE
    std::cout << "Tree is built" << std::endl;
    scene.capture_image(img);

    img.save();
    return 0;
}
