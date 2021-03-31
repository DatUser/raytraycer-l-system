#pragma once

#include <vector>
#include "image.hh"

struct SurfaceInfo
{
  //Color
  Color color;
  float kd;
  float ks;
  float ns;
};

class Texture_Material
{
  public:

    Texture_Material(std::vector<Color>& surface, float kd, float ks, float ns)
    : surface(surface),
      kd(kd),
      ks(ks),
      ns(ns)
    {
    }

    virtual SurfaceInfo get_point_info(unsigned int x, unsigned int y) const
      = 0;

    ~Texture_Material()
    {
      //free(surface);
    }

  protected:
    //Surface color
    std::vector<Color> surface;
    //Diffuse Component
    float kd;//[0 - 1]
    //Specular component
    float ks;//[0 - 1]
    float ns;
};
