#include <fstream>
#include "testing-model.h"

Tester::Tester(std::string &image_file_path, std::string &label_file_path, std::string &probabilities_file_path) {
    image_path = image_file_path;
    label_path = label_file_path;
    probabilities_path = probabilities_file_path;
}
void Tester::RunTester() {
    int num_total_images = 0;
    int num_correct_images = 0;
    std::ifstream infile(image_path);
    std::ifstream infile2(label_path);
    std::ifstream infile3(probabilities_path);
    while (ReadNextImage(infile) && SetNextClass(infile2)) {
        InitializeClassProbs();
        SetCurrentImage();
        UpdateProbs(infile3);
        UsePriors(infile3);
        UpdateWinningDigit();
        if (winning_digit == correct_class) {
            num_correct_images++;
        }
        num_total_images++;
    }
    std::cout << CalculateAccuracy(num_correct_images, num_total_images) << std::endl;
}
void Tester::UpdateWinningDigit() {
    int max_class = -1;
    double max_value = -1;
    for (int num_class = 0; num_class < NUM_CLASSES; num_class++) {
        if (class_probabilities[num_class] > max_value) {
            max_value = class_probabilities[num_class];
            max_class = num_class;
        }
    }
    winning_digit = max_class;
}

double Tester::CalculateAccuracy(int num_correct, int num_total) {
    return ((double) num_correct)/((double) num_total);
}
void Tester::UpdateProbs(std::ifstream &infile3) {
    std::string line;
    bool temp_is_shaded;
    for (int char_num = 0; char_num < IMAGE_SIZE; char_num++) {
        for (int line_num = 0; line_num < IMAGE_SIZE; line_num++) {
            temp_is_shaded = current_image.GetImagePixelAt(char_num, line_num) != 0;
            for (int num_class = 0; num_class < NUM_CLASSES; num_class++) {
                std::getline(infile3, line);
                SplitString(line);
                UpdateProbForClass(num_class, temp_is_shaded);
            }
        }
    }
}
void Tester::UsePriors(std::ifstream &infile3) {
    std::string line;
    double current_prior;
    for (int num_class = 0; num_class < NUM_CLASSES; num_class++) {
        std::getline(infile3, line);
        current_prior = std::stod (line);
        class_probabilities[num_class] += log (current_prior);
    }
}

void Tester::SplitString(std::string &line) {
    std::string unshaded_str;
    std::string shaded_str;
    int space_index;
    for (int char_num = 0; char_num < line.length(); char_num++) {
        if (line[char_num] == ' ') {
            space_index = char_num;
            break;
        }
    }
    unshaded_str = line.substr(0, space_index);
    shaded_str = line.substr(space_index);
    current_unshaded_prob = std::stod (unshaded_str);
    current_shaded_prob = std::stod (shaded_str);
}

void Tester::UpdateProbForClass(int num_class, bool isShaded) {
    if (isShaded) {
        class_probabilities[num_class] += log (current_shaded_prob);
    }
    else {
        class_probabilities[num_class] += log (current_unshaded_prob);
    }
}
bool Tester::ReadNextImage(std::ifstream &infile) {
    raw_image = "";
    std::string line;
    for (int line_num = 0; line_num < IMAGE_SIZE; line_num++) {
        std::getline(infile, line);
        if (line.empty()) {
            return false;
        }
        raw_image += line;
    }
    return true;
}
bool Tester::SetNextClass(std::ifstream &infile2) {
    std::string line;
    std::getline(infile2, line);
    if (line.empty()) {
        return false;
    }
    correct_class = line[0] - '0';
    return true;
}
void Tester::SetCurrentImage() {
    current_image = Image();
    current_image.ParseImage(raw_image);
}
void Tester::InitializeClassProbs() {
    for (double & class_probability : class_probabilities) {
        class_probability = 1;
    }
}
