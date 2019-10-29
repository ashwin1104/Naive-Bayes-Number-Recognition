#pragma once

#include <cstdlib>
#include <string>

constexpr size_t IMAGE_SIZE = 28;

class Image {
private:
    int pixels[IMAGE_SIZE][IMAGE_SIZE];
public:
    bool ParseImage(std::string current_image);
    int GetImagePixelAt(int row, int col);
};
