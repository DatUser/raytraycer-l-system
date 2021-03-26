#include "image.hh"
#include <fstream>
#include <ostream>

Image::Image(unsigned int width, unsigned int height)
: width(width),
  height(height),
  pixels(new uint8_t[width * height * 3])
{
}

Image::~Image()
{
    delete[] pixels;
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

void Image::put_pixel(unsigned int x, unsigned int y, Color& color)
{
  if (x < height && y < width)
  {
    pixels[(x * width + y) * 3] = static_cast<uint8_t>(color.x * 255.0);
    pixels[(x * width + y) * 3 + 1] = static_cast<uint8_t>(color.y * 255.0);;
    pixels[(x * width + y) * 3 + 2] = static_cast<uint8_t>(color.z * 255.0);;
  }
}

void Image::save_file()
{
    std::ofstream file("out.txt");

    for (unsigned int x = 0; x < height; x++)
    {
        for (unsigned int y = 0; y < width; y++)
        {
            file << '(' << (int) pixels[(x * width + y) * 3] << ',';
            file << (int) pixels[(x * width + y) * 3 + 1] << ',';
            file << (int) pixels[(x * width + y) * 3 + 2] << ')';
        }
        file << std::endl;
    }

    file.close();
}
