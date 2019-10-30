#include <fstream>
#include "testing-model.h"

Tester::Tester(std::string &image_file_path, std::string &label_file_path) {
    image_path = image_file_path;
    label_path = label_file_path;
    // the path that training-model wrote to for probabilities (hardcoded)
    probabilities_path = "/Users/ashwinsaxena/CLionProjects/naive-numbers-ashwin1104/libbayes/src/training-data.txt";
}
void Tester::RunTester() {
    int num_total_images = 0;
    int num_correct_images = 0;

    std::ifstream infile(image_path);
    std::ifstream infile2(label_path);

    // loops through each image
    while (ReadNextImage(infile) && SetNextClass(infile2)) {
        std::ifstream infile3(probabilities_path);

        InitializeClassProbs();
        SetCurrentImage();
        UpdateProbs(infile3);
        UsePriors(infile3);
        UpdateWinningDigit();

        if (winning_digit == correct_class) {
            num_correct_images++;
        }
        num_total_images++;
        infile3.close();
    }
    infile.close();
    infile2.close();
    std::cout << "Accuracy of Model: " << CalculateAccuracy(num_correct_images, num_total_images) << std::endl;
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

void Tester::UpdateProbs(std::ifstream &infile3) {
    std::string line;
    bool temp_is_shaded;
    for (int char_num = 0; char_num < IMAGE_SIZE; char_num++) {
        for (int line_num = 0; line_num < IMAGE_SIZE; line_num++) {
            temp_is_shaded = current_image.GetImagePixelAt(char_num, line_num) != 0;
            for (int num_class = 0; num_class < NUM_CLASSES; num_class++) {
                std::getline(infile3, line);
                SplitString(line);
                // calls on this function for each pixel, given the class, for the given image
                UpdateProbForClass(num_class, temp_is_shaded);
            }
        }
    }
}

void Tester::UsePriors(std::ifstream &infile3) {
    std::string line;
    double current_prior;
    for (double & class_probabilitie : class_probabilities) {
        std::getline(infile3, line);
        current_prior = std::stod (line);
        class_probabilitie += log (current_prior);
    }
}

void Tester::UpdateProbForClass(int num_class, bool isShaded) {
    if (isShaded) {
        class_probabilities[num_class] += log (current_shaded_prob);
    }
    else {
        class_probabilities[num_class] += log (current_unshaded_prob);
    }
}

void Tester::UpdateWinningDigit() {
    int max_class = -1;
    double max_value = -DBL_MAX;
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

void Tester::InitializeClassProbs() {
    for (double & class_probability : class_probabilities) {
        class_probability = 0;
    }
}

void Tester::SplitString(std::string &line) {
    std::string unshaded_str;
    std::string shaded_str;
    int space_index = 0;
    // splits string by a space
    for (char c : line) {
        if (c == ' ') {
            break;
        }
        space_index++;
    }
    unshaded_str = line.substr(0, space_index);
    shaded_str = line.substr(space_index + 1);
    current_unshaded_prob = std::stod (unshaded_str);
    current_shaded_prob = std::stod (shaded_str);
}
