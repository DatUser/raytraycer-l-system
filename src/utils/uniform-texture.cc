#include "uniform-texture.hh"

Uniform_Texture::Uniform_Texture(std::vector<Color>& color, float kd, float ks)
: Texture_Material(color, kd, ks)
{}

SurfaceInfo Uniform_Texture::get_point_info(unsigned int x, unsigned int y)
  const
{
  (void) x;
  (void) y;

  return SurfaceInfo
  {
    surface[0],
    kd,
    ks
  };
}
