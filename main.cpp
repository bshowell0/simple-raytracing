#include <limits>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include "geometry.h"

void render()
{
    const int width = 1280;
    const int height = 720;
    std::vector<Vec3f> framebuffer(width * height);

    for (size_t j = 0; j < height; j++)
    {
        for (size_t i = 0; i < width; i++)
        {
            framebuffer[i + j * width] = Vec3f(j / float(height), i / float(width), 0);
        }
    }

    std::ofstream ofs;  // save the framebuffer to RAW RGB file (ppm for testing)
    ofs.open("./output.ppm", std::ios::binary);  // change to .rgb once done
    ofs << "P6 " << width << " " << height << " 255 ";  // delete once done
    for (size_t i = 0; i < height * width; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            ofs << (char)(255 * std::max(0.f, std::min(1.f, framebuffer[i][j])));
        }
    }

    ofs.close();
}

int main()
{
    render();
    return 0;
}