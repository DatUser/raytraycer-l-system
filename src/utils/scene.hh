#pragma once

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

  private:
    Vector3 project_vector(const Vector3& v, const Vector3& x_basis,
	const Vector3& y_basis, const Vector3& z_basis,
	const Vector3& translation) const;

    void compute_light(Point3& hitpoint, const Object& object);

    SurfaceInfo find_color(const Vector3& v, const Vector3& forward) const;

    std::vector<Object*> objects;
    std::vector<Light> lights;
    Camera camera;
};
