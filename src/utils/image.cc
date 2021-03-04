#include "image.hh"
#include <ostream>

Image::Image(unsigned int width, unsigned int height)
: width(width),
  height(height)
{}

Image::~Image()
{
  delete pixels;
}

void Image::save()
{
  std::ofstream ofs("render.ppm", std::ios::binary);
  ofs << "P6 1920 1080 255" << std::endl;

  for (unsigned int x = 0; x < height; x++)
  {
    for (unsigned int y = 0; y < width; y++)
    {
      ofs << pixels[(x * width + height) * 3];
      ofs << pixels[(x * width + height) * 3 + 1];
      ofs << pixels[(x * width + height) * 3 + 2];
    }
    ofs << std::endl;
  }

  ofs.close();
}

void Image::put_pixel(unsigned int x, unsigned int y, uint8_t r, uint8_t g,
    uint8_t b)
{
  if (x < height && y <= width)
  {
    pixels[(x * width + y) * 3] = r;
    pixels[(x * width + y) * 3 + 1] = g;
    pixels[(x * width + y) * 3 + 2] = b;
  }
}
