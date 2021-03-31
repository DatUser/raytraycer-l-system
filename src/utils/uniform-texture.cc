#include "uniform-texture.hh"

Uniform_Texture::Uniform_Texture(std::vector<Color>& color, float kd, float ks, float ns)
: Texture_Material(color, kd, ks, ns)
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
    ks,
    ns
  };
}
