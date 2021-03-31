#pragma once

#include <cstdint>
#include <fstream>
#include <vector>
#include <utils/vector3.hh>

class Image
{
  public:
    Image(unsigned int width, unsigned int height);

    ~Image();

    void save();

    void put_pixel(unsigned int x, unsigned int y, Color& color);

    void save_file();

  //private:
    unsigned int width;
    unsigned int height;
    std::vector<uint8_t > pixels;
};
