#include "image.hh"
#include <fstream>
#include <ostream>

Image::Image(unsigned int width, unsigned int height)
: width(width),
  height(height)
{
  pixels = (RGB8) aligned_alloc(TL_IMAGE_ALIGNMENT, width * height * 3);
}

Image::~Image()
{
  free(pixels);
}

void Image::save()
{
  std::ofstream ofs("render.ppm", std::ofstream::out);//, std::ios::binary);
  ofs << "P3\n" << width << " " << height << "\n" << "255" << std::endl;

  for (unsigned int x = 0; x < height; x++)
  {
    for (unsigned int y = 0; y < width; y++)
    {
      ofs << (int) pixels[(x * width + y) * 3] << ' ';
      ofs << (int) pixels[(x * width + y) * 3 + 1] << ' ';
      ofs << (int) pixels[(x * width + y) * 3 + 2] << ' ';
    }
    ofs << std::endl;
  }

  ofs.close();
}

void Image::put_pixel(unsigned int x, unsigned int y, uint8_t r, uint8_t g,
    uint8_t b)
{
  if (x < height && y < width)
  {
    pixels[(x * width + y) * 3] = r;
    pixels[(x * width + y) * 3 + 1] = g;
    pixels[(x * width + y) * 3 + 2] = b;
  }
}
