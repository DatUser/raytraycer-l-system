#include <iostream>
#include <iterator>
#include <utils/point3.hh>
#include <utils/image.hh>
#include <utils/uniform-texture.hh>
#include <utils/sphere.hh>
#include <utils/camera.hh>
#include <utils/scene.hh>

int main()
{
  Image img(1920, 1080);
  Point3 center_s1(0, 0, 20);
  RGB8 color = (RGB8) aligned_alloc(TL_IMAGE_ALIGNMENT, 3);
  color[0] = 255;
  color[1] = 0;
  color[2] = 0;
  Texture_Material* texture = new Uniform_Texture(color, 0.5, 0.5);
  Sphere s1(center_s1, 3, texture);

  Point3 center_s2(10, 0, 20);
  RGB8 color2 = (RGB8) aligned_alloc(TL_IMAGE_ALIGNMENT, 3);
  color2[0] = 0;
  color2[1] = 255;
  color2[2] = 0;
  Texture_Material* texture2 = new Uniform_Texture(color2, 0.5, 0.5);
  Sphere s2(center_s2, 3, texture2);

  Point3 center_cam(0, 0, 0);
  Vector3 up(0, 1, 0);
  Camera camera(center_cam, center_s1, up, 120, 80, 15);

  //TEST
  Vector3 project_p(50, 0, 15);
  Vector3 u_vec(0, 0, 1);
  auto intersection = s2.intersect(project_p, u_vec);
  if (intersection.has_value())
    std::cout << "This is touching" << std::endl;
  else
    std::cout << "No intersection" << std::endl;
  //

  Scene scene(camera);
  scene.add_object(&s1);
  scene.add_object(&s2);
  scene.capture_image(img);

  img.save();

  /*free(texture);
  free(texture2);*/

  return 0;
}
