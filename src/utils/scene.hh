#pragma once

#define MAX_DEPTH 3

#include <vector>
#include <limits>
#include "object.hh"
#include "light.hh"
#include "camera.hh"

class Scene
{
  public:
    Scene(Camera camera);

    void capture_image(Image& image) const;

    void add_object(Object* object);

    void add_light(Light& light);

  private:
    Vector3 project_vector(const Point3& origin, const Vector3& x_basis,
	const Vector3& y_basis, const Vector3& z_basis,
	const Vector3& translation) const;
    bool intersect(const Point3& origin, const Vector3& direction, const Object* source) const;

    Color compute_light(const Point3& origin, const Point3& hitpoint, const Object* object, int depth) const;

    Color find_color(const Vector3& v, const Vector3& forward, int depth, const Object* source= nullptr) const;

    std::vector<Object*> objects;
    std::vector<Light> lights;
    Camera camera;
};
