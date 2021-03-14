#pragma once

#include <cstdint>
#include <fstream>

#define TL_IMAGE_ALIGNMENT 64

typedef uint8_t* __restrict__ __attribute__((aligned(TL_IMAGE_ALIGNMENT))) RGB8;

class Image
{
  public:
    Image(unsigned int width, unsigned int height);

    ~Image();

    void save();

    void put_pixel(unsigned int x, unsigned int y, uint8_t r, uint8_t g,
	uint8_t b);

  //private:
    unsigned int width;
    unsigned int height;
    RGB8 pixels;
};
