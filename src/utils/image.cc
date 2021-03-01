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
  std::ofstream ofs("render.ppm");
  ofs << "P6 1920 1080 255" << std::endl;



  ofs.close();
}
