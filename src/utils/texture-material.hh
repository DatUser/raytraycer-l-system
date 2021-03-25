#pragma once

#include "image.hh"

struct SurfaceInfo
{
  //Couleur
  Color color;
  float kd;
  float ks;
};

class Texture_Material
{
  public:

    Texture_Material(std::vector<Color>& surface, float kd, float ks)
    : surface(surface),
      kd(kd),
      ks(ks)
    {
    }

    virtual SurfaceInfo get_point_info(unsigned int x, unsigned int y) const
      = 0;

    ~Texture_Material()
    {
      //free(surface);
    }

  protected:
    //Couleurs de la surface
    std::vector<Color> surface;
    //Composant diffuse
    float kd;//[0 - 1]
    //Composante speculaire
    float ks;//[0 - 1]
};
