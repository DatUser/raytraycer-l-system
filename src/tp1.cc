#include <iostream>
#include <iterator>
#include <utils/point3.hh>
#include <utils/image.hh>
#include <utils/uniform-texture.hh>
#include <utils/sphere.hh>
#include <utils/camera.hh>
#include <utils/scene.hh>
#include <utils/triangle.hh>
#include <utils/plane.hh>
#include <parser/parser.hh>
#include <parser/print-visitor.hh>

int maintmp() {
    Image img(1920, 1080);
    Point3 center_s1(-5, 0, 20);
    //Color color{0.71,0.1,0.1};
    Color color{0.71, 0.1, 0};
    std::vector<Color> colors_t1;
    colors_t1.push_back(color);
    Texture_Material *texture = new Uniform_Texture(colors_t1, 0.7, 0.1, 2);
    Sphere s1(center_s1, 3, texture);

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

    Point3 center_cam(0, 10, 10);
    Vector3 up = Vector3(0, 1, 1).get_normalized();
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
    Point3 light_pos(0, 7, 20);
    Light light(light_pos, 1, 1, 1);

    Scene scene(camera);
    scene.add_object(&s1);
    scene.add_object(&s2);
    scene.add_object(&s3);
    //scene.add_object(&plane);
    scene.add_object(&t1);
    scene.add_light(light);
    scene.capture_image(img);

    //Fix reflection issue
    /*Color c = Color(0,0,1);
    img.put_pixel(835, 1033,c);*/

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
    Parser parser("test");

    //std::string rule = "F+F+F+F";
    std::string rule = "[+F][-F]";
    Point3 origin = Point3(0,0,0);
    Vector3 direction = Vector3(0,1,0);
    Node* node = parser.build_rule(rule, origin, direction, 2, 90);
    PrintVisitor printVisitor;

    node->accept(printVisitor);

    delete node;
}
