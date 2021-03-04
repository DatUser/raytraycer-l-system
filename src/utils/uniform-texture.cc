#include "uniform-texture.hh"

Uniform_Texture::Uniform_Texture(RGB8 color, float kd, float ks)
: Texture_Material(color, kd, ks)
{}

SurfaceInfo Uniform_Texture::get_point_info(unsigned int x, unsigned int y)
  const
{
  if (x == y)
    return SurfaceInfo
    {
      surface,
      kd,
      ks
    };

  return SurfaceInfo
  {
    surface,
    kd,
    ks
  };
}
