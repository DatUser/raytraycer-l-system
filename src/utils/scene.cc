#include "scene.hh"
#include <cmath>
#include <iostream>
#include <iterator>
#include <ostream>

Scene::Scene(Camera camera)
: objects(std::vector<Object*>()),
  lights(std::vector<Light>()),
  camera(camera)
{}

// Angle in degree
void rotateAroundY(Vector3& v, float angle)
{
  float rad_angle = angle * (M_PI / 180);
  float tmp_x = v.x;
  float tmp_z = v.z;
  v.x = tmp_x * cos(rad_angle) + tmp_z * sin(rad_angle);
  v.z = -tmp_x * sin(rad_angle) + tmp_z * cos(rad_angle);
}

void rotateAroundX(Vector3& v, float angle)
{
  float rad_angle =   angle * (M_PI / 180);
  float tmp_y = v.y;
  float tmp_z = v.z;
  v.y = tmp_y * cos(rad_angle) - tmp_z * sin(rad_angle);
  v.z = tmp_y * sin(rad_angle) + tmp_z * cos(rad_angle);
}

Vector3 Scene::project_vector(const Vector3& v, const Vector3& x_basis,
    const Vector3& y_basis, const Vector3& z_basis,
    const Vector3& translation) const
{
  float x_world = v.x * x_basis.x + v.y * y_basis.x + v.z * z_basis.x
    + translation.x;
  float y_world = v.x * x_basis.y + v.y * y_basis.y + v.z * z_basis.y
    + translation.y;
  float z_world = v.x * x_basis.z + v.y * y_basis.z + v.z * z_basis.z
    + translation.z;
  return Vector3(x_world - camera.center.x, y_world - camera.center.y,
      z_world - camera.center.z);
}

SurfaceInfo Scene::find_color(const Vector3& v, const Vector3& forward) const
{
  float closest = std::numeric_limits<float>::max();
  SurfaceInfo info = { nullptr, 0, 0 };

  std::optional<Vector3> intersection;
  float p_norm = 0;

  /*Vector3 forward2(v.x - camera.center.x, v.y - camera.center.y, v.z - camera.center.z);
  if (forward.z == 1)
    forward2.normalize();*/

  for (unsigned int i = 0; i < objects.size(); i++)
  {
    const Object* obj = objects[i];
    if ((intersection = obj->intersect(/*camera.center, v*/v, forward)).has_value() &&
	  (p_norm = norm(camera.center, intersection.value())) < closest) 
    {
      closest = p_norm;
      info = obj->get_texture(intersection.value());
    }
  }

  return info;
}

void Scene::compute_light(Point3& hitpoint, const Object& object)
{
    for (unsigned int i = 0; i < lights.size(); i++)
    {

    }
}

void Scene::capture_image(Image& image) const
{
  float width = (camera.z_pos * tan(camera.x_angle / 2 * M_PI / 180)) * 2 ;
  float left_shift = width / 2;
  float height = (camera.z_pos * tan(camera.y_angle / 2 * M_PI / 180)) * 2 ;
  float down_shift = height / 2;

  Vector3 y = camera.up;
  Vector3 z = Vector3(camera.center, camera.target).get_normalized();
  Vector3 x = y * z;
  Vector3 translation = Vector3(camera.center.x, camera.center.y,
      camera.center.z);

  for (unsigned int i = 0; i < image.height; i++)
  {
    float v_y = (image.height - i - 0.5) * height / image.height - down_shift;
    //std::cout << "vector y is: " << v_y << std::endl;
    //std::cout << begin << "-->";
    for (unsigned int j = 0; j < image.width; j++)
    {
      float v_x =  (j + 0.5)  * width / image.width - left_shift;
      /*if (i == 0)
        std::cout << "vector x is: " << v_x << std::endl;*/

      Vector3 projection = project_vector(Vector3(v_x, v_y, camera.z_pos), x, y, z,
	  translation);

      /*if (i == 0)
	std::cout << projection << std::endl;*/

      //projection.normalize();
      SurfaceInfo texture = find_color(projection, z);
      if (texture.color)
      {
          image.put_pixel(i, j, texture.color[0], texture.color[1],
                          texture.color[2]);
      }
      else
        image.put_pixel(i, j, 0, 0, 0);
      
      //shifts right
      //rotateAroundY(begin, right_shift);
    }
    //std::cout << begin << std::endl;

    //shifts left
    //rotateAroundY(begin, -camera.x_angle);
    //shifts down
    //rotateAroundX(begin, down_shift);
  }
}

void Scene::add_object(Object* object)
{
  objects.push_back(object);
}
