#pragma once

#include "texture-material.hh"
#include "image.hh"
#include "vector3.hh"

class Ppm_Texture : public Texture_Material
{
public:

    Ppm_Texture(std::string filename, std::vector<Color> &color, float kd, float ks, float ns);

    ~Ppm_Texture();

    SurfaceInfo get_point_info(float x, float y) const final;

    Image ppm_texture;
};
