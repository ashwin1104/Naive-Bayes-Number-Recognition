#include <fstream>
#include "validate-file.h"
#include "model.hpp"
Validate::Validate(std::string &images) {
    images_file_path = images;
    image_num_lines = 0;
    label_num_lines = 0;
}

Validate::Validate(std::string &images, std::string &labels) {
    images_file_path = images;
    labels_file_path = labels;
    image_num_lines = 0;
    label_num_lines = 0;
}
bool Validate::ValidateImage() {
    SetValImageChars();
    std::ifstream infile(images_file_path);
    if (infile.is_open()) {
        std::string line;
        while (std::getline(infile, line)) {
            if (line.empty()) {
                break;
            }
            if (!(ValImageNumCharsInLine(line) && ValImageTypeChars(line))) {
                return false;
            }
            image_num_lines++;
        }
    }
    else {
        return false;
    }
    infile.close();
    return ValImageNumLines();
}
bool Validate::ValidateLabel() {
    SetValLabelChars();
    std::ifstream infile(labels_file_path);
    if (infile.is_open()) {
        std::string line;
        while (std::getline(infile, line)) {
            if (line.empty()) {
                break;
            }
            if (!(ValLabelNumChars(line) && ValLabelTypeChars(line))) {
                return false;
            }
            label_num_lines++;
        }
    }
    else {
        return false;
    }
    infile.close();
    return ValLabelNumLines();
}

bool Validate::ValImageNumLines() {
    return image_num_lines % 28 == 0;
}
bool Validate::ValImageNumCharsInLine(std::string &line) {
    return line.length() == 28;
}
bool Validate::ValImageTypeChars(std::string &line) {
    if (line.empty()) {
        return false;
    }
    for (char c : line) {
        if (valid_image_chars.find(c) == valid_image_chars.end()) {
            return false;
        }
    }
    return true;
}

bool Validate::ValLabelNumChars(std::string &line) {
    return line.length() == 1;
}
bool Validate::ValLabelTypeChars(std::string &line) {
    if (line.empty()) {
        return false;
    }
    return valid_label_chars.find(line[0]) != valid_label_chars.end();
}
bool Validate::ValLabelNumLines() {
    return label_num_lines*28 == image_num_lines;
}
void Validate::SetValImageChars() {
    valid_image_chars.insert(' ');
    valid_image_chars.insert('#');
    valid_image_chars.insert('+');
}
void Validate::SetValLabelChars() {
    char temp_valid_char;
    for (int valid_int = 0; valid_int < NUM_CLASSES; valid_int++) {
        temp_valid_char = valid_int + '0';
        valid_label_chars.insert(temp_valid_char);
    }
}
std::string Validate::GetImagesFile() {
    return images_file_path;
}
std::string Validate::GetLabelsFile() {
    return labels_file_path;
}