#pragma once

#include "texture-material.hh"

class Uniform_Texture : public Texture_Material
{
  public:

    Uniform_Texture(std::vector<Color>& color, float kd, float ks, float ns);

    ~Uniform_Texture();

    SurfaceInfo get_point_info(float x, float y) const final;
};
