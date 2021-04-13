#include <iostream>
#include <iterator>
#include <utils/point3.hh>
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

int main1() {
    Image img(1920, 1080);
    Point3 center_s1(-5, 0, 20);
    //Color color{0.71,0.1,0.1};
    Color color{0.71, 0.1, 0};
    std::vector<Color> colors_t1;
    colors_t1.push_back(color);
    Texture_Material *texture = new Uniform_Texture(colors_t1, 0.7, 0.1, 2);
    Sphere s1(center_s1, 3, texture);

    Color color_cylinder{0, 1, 0};
    std::vector<Color> colors_cylinder;
    colors_cylinder.push_back(color_cylinder);

    Point3 bas(0, -5, 20);
    Point3 haut(0,0,20);
    Texture_Material *texture_cylindre = new Uniform_Texture(colors_cylinder, 1, 1, 10);
    Cylinder cylinder(bas, haut, 0.2, texture_cylindre);

    Point3 bas2(-0.5, -2.5, 20);
    Point3 haut2(-1.5,0,20);
    Texture_Material *texture_cylindre2 = new Uniform_Texture(colors_cylinder, 1, 1, 10);
    Cylinder cylinder2(bas2, haut2, 0.2, texture_cylindre2);

    Point3 bas3(2.2, -2.5, 20);
    Point3 haut3(2.2,-2.5,23);
    Texture_Material *texture_cylindre3 = new Uniform_Texture(colors_cylinder, 1, 1, 10);
    Cylinder cylinder3(bas3, haut3, 0.2, texture_cylindre3);

    Point3 center_s2(5, 0, 20);
    //Color color2{0.1,0.71,0.1};
    Color color2{0.1, 0.71, 0};
    std::vector<Color> colors_t2;
    colors_t2.push_back(color2);
    Texture_Material *texture2 = new Uniform_Texture(colors_t2, 0.7, 0.1, 20);
    Sphere s2(center_s2, 3, texture2);

    Point3 center_s3(5, -2005, 20);
    //Color color2{0.1,0.71,0.1};
    Color color3{0.8, 0.8, 0.8};
    std::vector<Color> colors_t3;
    colors_t3.push_back(color3);
    Texture_Material *texture3 = new Uniform_Texture(colors_t3, 0.7, 0.1, 20);
    Sphere s3(center_s3, 2000, texture3);

    /*Point3 plane_O(0,-5,0);
    Point3 plane_x(1,-5,0);
    Point3 plane_y(0,-5,1);
    Color color3(1,1,1);
    std::vector<Color> colors_p;
    colors_p.push_back(color3);
    Texture_Material *textureP = new Uniform_Texture(colors_p, 0.7, 0.1, 20);
    Plane plane(plane_O,plane_x,plane_y, textureP);*/

    Point3 center_cam(0, 0, 0);
    Vector3 up = Vector3(0, 1, 0).get_normalized();
    Point3 target(0, 0, 20);
    Camera camera(center_cam, target, up, 90, 90 * ((float)img.height / (float) img.width), 10);

    Point3 a(0, 0, 20);
    Point3 b(-5, 0, 20);
    Point3 c(0, 5, 20);
    /*RGB8 color3 = (RGB8) aligned_alloc(TL_IMAGE_ALIGNMENT, 3);
    color2[0] = 0;
    color2[1] = 0;
    color2[2] = 255;*/
    Color color4{0.1, 0.1, 0.8};
    std::vector<Color> colors_t4;
    colors_t4.push_back(color4);
    Texture_Material* texture4 = new Uniform_Texture(colors_t4, 0.7, 0.1,20);
    Triangle t1(b, a, c, texture4);

    //TEST
    /*Vector3 project_p(0, 0, -15);
    Vector3 u_vec(0, 0, -1);
    auto intersection = t1.intersect(project_p, u_vec);
    if (intersection.has_value())
      std::cout << "This is touching" << std::endl;
    else
      std::cout << "No intersection" << std::endl;*/
    //
    Point3 light_pos(3, 7, 0);
    Light light(light_pos, 1, 1, 1);

    Scene scene(camera);
    scene.add_object(&s1);
//    scene.add_object(&s2);
    scene.add_object(&s3);
    scene.add_object(&cylinder);
    scene.add_object(&cylinder2);
    scene.add_object(&cylinder3);
//    scene.add_object(&plane);
    //scene.add_object(&t1);
    scene.add_light(light);
    scene.capture_image(img);

    //Fix reflection issue
    //    Color c = Color(0,0,1);
    //    img.put_pixel(820, 960,c);

    //Fix light problem
    /*Color c = Color(1,0,0);
    img.put_pixel(530, 850,c);*/

    //Fix border lights
    /*Color c1 = Color(0,0,1);
    int shift = 750;
    img.put_pixel(530, shift,c1);
    Color c2 = Color(0,0,1);
    img.put_pixel(530, 1920 - 1 - shift,c2);*/

    img.save();
    //img.save_file();


    return 0;
}

int main()
{
    //SCENE CREATION
    Image img(1920, 1080);

    Point3 light_pos(3, 7, 0);
    Light light(light_pos, 1, 1, 1);

    Point3 center_cam(0, 0, 0);
    Vector3 up = Vector3(0, 1, 0).get_normalized();
    Point3 target(0, 0, 20);
    Camera camera(center_cam, target, up, 90, 90 * ((float)img.height / (float) img.width), 10);

    Point3 center_s3(5, -2005, 20);
    //Color color2{0.1,0.71,0.1};
    Color color3{0.8, 0.8, 0.8};
    std::vector<Color> colors_t3;
    colors_t3.push_back(color3);
    Texture_Material *texture3 = new Uniform_Texture(colors_t3, 0.7, 0.1, 20);
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
    std::string rule_s = "F";

    //BUILDING RULE'S TREE
    std::map<char, Node*> rules;

    Point3 origin = Point3(0,-5,15);
    Vector3 direction = Vector3(0,1,1).get_normalized();
    Node* rule_node_a = parser.build_rule(rule_a, origin, direction, 1, 90, 0.2);
    rules.insert({'A', rule_node_a});

    Node* rule_node_f = parser.build_rule(rule_f, origin, direction, 1, 90, 0.2);
    rules.insert({'F', rule_node_f});

    Node* rule_node_s = parser.build_rule(rule_s, origin, direction, 1, 90, 0.2);
    rules.insert({'S', rule_node_s});

    Node* sentence_node = parser.build_rule(sentence, origin, direction, 5, 22.5, 0.15);
    PrintVisitor printVisitor(1, rules);
    GenerateVisitor generateVisitor(&scene, 5, rules, 0.75);

    //VISITING TREE
    sentence_node->accept(generateVisitor);
    //sentence_node->accept(printVisitor);
    //rule_node->accept(generateVisitor);
    //parser.parse(sentence, rules, printVisitor);

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
