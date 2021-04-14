#include "ppm-texture.hh"

Ppm_Texture::Ppm_Texture(std::string filename, std::vector<Color> &color, float kd, float ks, float ns): Texture_Material(color, kd, ks, ns),
                                                                                                         ppm_texture(
                                                                                                                 Image(filename)) {

}

SurfaceInfo Ppm_Texture::get_point_info(float x, float y) const {
    x = x * ppm_texture.width;
    y = y * ppm_texture.height;
    Color res = ppm_texture.get_pixel(x, y);
    return SurfaceInfo
            {
                    res,
                    kd,
                    ks,
                    ns
            };
}
