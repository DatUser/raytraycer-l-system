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
//#include <utils/plane.hh>

int main() {
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

    /*Point3 a(0, 0, -20);
    Point3 b(-5, 0, -20);
    Point3 c(0, 5, -20);
    RGB8 color3 = (RGB8) aligned_alloc(TL_IMAGE_ALIGNMENT, 3);
    color2[0] = 0;
    color2[1] = 0;
    color2[2] = 255;
    Texture_Material* texture3 = new Uniform_Texture(color3, 0.5, 0.5);
    Triangle t1(a, b, c, texture3);*/

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
