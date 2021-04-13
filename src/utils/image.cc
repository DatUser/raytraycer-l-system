#include "image.hh"
#include <fstream>
#include <ostream>
#include <vector>

Image::Image(unsigned int width, unsigned int height)
        : width(width),
          height(height),
          pixels(std::vector<uint8_t>(width * height * 3)) {
}

Image::~Image() {
}

void Image::save() {
    std::ofstream ofs("render.ppm", std::ofstream::out);//, std::ios::binary);
    ofs << "P3\n" << width << " " << height << "\n" << "255" << std::endl;

    for (unsigned int x = 0; x < height; x++) {
        for (unsigned int y = 0; y < width; y++) {
            ofs << (int) pixels[(x * width + y) * 3] << ' ';
            ofs << (int) pixels[(x * width + y) * 3 + 1] << ' ';
            ofs << (int) pixels[(x * width + y) * 3 + 2] << ' ';
        }
        ofs << std::endl;
    }

    ofs.close();
}

void Image::put_pixel(unsigned int x, unsigned int y, Color &color) {
    if (x < height && y < width) {

        if (color.x > 1 || color.y > 1 || color.z > 1)
            std::cout << "tout cassé" << std::endl;

        pixels[(x * width + y) * 3] = static_cast<uint8_t>(color.x * 255.0);
        pixels[(x * width + y) * 3 + 1] = static_cast<uint8_t>(color.y * 255.0);;
        pixels[(x * width + y) * 3 + 2] = static_cast<uint8_t>(color.z * 255.0);;
    }
}

void Image::save_file() {
    std::ofstream file("out.txt");

    for (unsigned int x = 0; x < height; x++) {
        for (unsigned int y = 0; y < width; y++) {
            file << '(' << (int) pixels[(x * width + y) * 3] << ',';
            file << (int) pixels[(x * width + y) * 3 + 1] << ',';
            file << (int) pixels[(x * width + y) * 3 + 2] << ')';
        }
        file << std::endl;
    }

    file.close();
}

Color Image::get_pixel(unsigned int x, unsigned int y) {
    float R, G, B;
    R = pixels[(x * width + y) * 3];
    G = pixels[(x * width + y) * 3 + 1];
    B = pixels[(x * width + y) * 3 + 2];
    return Color(R / 255, G / 255, B / 255);
}

bool Image::gradient(unsigned int x, unsigned int y, float gradient) {
    (void) gradient;
    // -------------
    // | a | b | c |
    // -------------
    // | d | e | f |
    // -------------
    // | g | h | i |
    // -------------

    auto a = get_pixel(x - 1 , y - 1);
    auto b = get_pixel(x, y - 1);
    auto c = get_pixel(x + 1, y - 1);

    auto d = get_pixel(x - 1, y);
    auto e = get_pixel(x, y);
    auto f = get_pixel(x + 1, y);

    auto g = get_pixel(x - 1, y + 1);
    auto h = get_pixel(x, y + 1);
    auto i = get_pixel(x + 1, y + 1);


    return a == b && a == c && a == d && a == e && a == f && a == g && a == h && a == i;
}
