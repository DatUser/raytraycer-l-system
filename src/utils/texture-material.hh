#pragma once

#include "image.hh"

struct SurfaceInfo
{
  //Couleur
  RGB8 color;
  float kd;
  float ks;
};

class Texture_Material
{
  public:

    Texture_Material(RGB8 surface, float kd, float ks)
    : surface(surface),
      kd(kd),
      ks(ks)
    {
    }

    virtual SurfaceInfo get_point_info(unsigned int x, unsigned int y) const
      = 0;

  protected:
    //Couleurs de la surface
    RGB8 surface;
    //Composant diffuse
    float kd;//[0 - 1]
    //Composante speculaire
    float ks;//[0 - 1]
};
