#pragma once

#include <vector>
#include <string>

constexpr size_t IMAGE_SIZE = 28;

class Image {
private:
    int pixels[IMAGE_SIZE][IMAGE_SIZE];
public:
    void ParseImage(std::string current_image);
    int GetImagePixelAt(int row, int col);
};
