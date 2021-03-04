#pragma once

#include <vector>
#include "object.hh"
//#include "light.hh"
//#include "camera.hh"

class Scene
{
  public:
    //Scene(Camera camera);

  private:
    std::vector<Object> objects;
    //std::vector<Light> lights;
    //Camera camera;
};
