#include "image.hpp"
#include <string>
#include <iostream>

void Image::ParseImage(std::string current_image) {
    for (int char_num = 0; char_num < IMAGE_SIZE; char_num++) {
        for (int line_num = 0; line_num < IMAGE_SIZE; line_num++) {
            if (current_image[char_num*IMAGE_SIZE +line_num] == ' ') {
                pixels[char_num][line_num] = 0;
            }
            else {
                pixels[char_num][line_num] = 1;
            }
        }
    }
}

int Image::GetImagePixelAt(int row, int col) {
    return pixels[row][col];
}