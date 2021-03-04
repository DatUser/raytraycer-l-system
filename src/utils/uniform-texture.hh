#pragma once

#include "texture-material.hh"

class Uniform_Texture : Texture_Material
{
  public:

    Uniform_Texture(RGB8 color, float kd, float ks);

    ~Uniform_Texture();

    SurfaceInfo get_point_info(unsigned int x, unsigned int y) const final;
};
