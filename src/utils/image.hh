#pragma once

#include <cstdint>
#include <fstream>

#define TL_IMAGE_ALIGNMENT 64

typedef uint8_t* __restrict__ __attribute__((aligned(TL_IMAGE_ALIGNMENT))) RGB8;

class Image
{
  Image(unsigned int width, unsigned int height);

  ~Image();

  void save();

  void put_pixel(unsigned int x, unsigned int y);

  private:
    unsigned int width;
    unsigned int height;
    RGB8 pixels;
};
