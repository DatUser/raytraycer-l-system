#include "uniform-texture.hh"

Uniform_Texture::Uniform_Texture(std::vector<Color> &color, float kd, float ks, float ns)
        : Texture_Material(color, kd, ks, ns) {}

SurfaceInfo Uniform_Texture::get_point_info(float x, float y)
const {
//    std::cout << "(x:" << x << ",y:" << y << ")" << std::endl;
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
