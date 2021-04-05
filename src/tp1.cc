#include <iostream>
#include <iterator>
#include <utils/point3.hh>
#include <utils/image.hh>
#include <utils/uniform-texture.hh>
#include <utils/sphere.hh>
#include <utils/camera.hh>
#include <utils/scene.hh>
#include <utils/triangle.hh>

int main() {
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

    Point3 center_cam(0, 0, 0);
    Vector3 up(0, 1, 0);
    Point3 target(0, 0, 15);
    Camera camera(center_cam, target, up, 120, 80, 15);

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
    Point3 light_pos(0, 7, 20);
    Light light(light_pos, 1, 1, 1);

    Scene scene(camera);
    scene.add_object(&s1);
    scene.add_object(&s2);
    //scene.add_object(&t1);
    scene.add_light(light);
    scene.capture_image(img);

    //Fix reflection issue
    /*Color c = Color(0,0,1);
    img.put_pixel(535, 1033,c);*/

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
    img.save_file();


    return 0;
}
