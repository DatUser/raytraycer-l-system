#pragma once

#include <cstdint>
#include <fstream>
#include <vector>
#include <utils/vector3.hh>
#include <string>

class Image
{
  public:
    Image(unsigned int width, unsigned int height);

    Image(std::string filename);

    ~Image();

    void save();

    void put_pixel(unsigned int x, unsigned int y, Color& color);

    Color get_pixel(unsigned int x, unsigned int y) const;

    bool gradient(unsigned x, unsigned y, float gradient);

    void save_file();

  //private:
    unsigned int width;
    unsigned int height;
    std::vector<uint8_t > pixels;
};
