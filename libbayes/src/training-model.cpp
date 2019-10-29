#include "training-model.h"
#include <fstream>

Training::Training(std::string &training_images, std::string &training_labels) {
    training_images_file = training_images;
    training_labels_file = training_labels;
    model = Model();
    k = 2;
}
void Training::RunTraining() {
    while (ReadNextImage() && SetNextClass()) {
        SetCurrentImage();
        UpdateProbs();
    }
    UpdateAllProbabilities();
    OutputProbabilities();
}
bool Training::ReadNextImage() {
    raw_image = "";
    std::string line;
    std::ifstream infile(training_images_file);
    for (int line_num = 0; line_num <= IMAGE_SIZE; line_num++) {
        std::getline(infile, line);
        if (line.empty()) {
            return false;
        }
        raw_image += line;
    }
    infile.close();
    return true;
}
bool Training::SetNextClass() {
    std::string line;
    std::ifstream infile(training_labels_file);
    std::getline(infile, line);
    if (line.empty()) {
        return false;
    }
    current_number_class = line[0] - '0';
    return true;
}
void Training::SetCurrentImage() {
    current_image = Image();
    current_image.ParseImage(raw_image);
}
void Training::UpdateProbs() {
    for (int char_num = 0; char_num < IMAGE_SIZE; char_num++) {
        for (int line_num = 0; line_num < IMAGE_SIZE; line_num++) {
            if (current_image.GetImagePixelAt(char_num, line_num) == 0) {
                model.probs[char_num][line_num][current_number_class][0] += 1;
            }
            else {
                model.probs[char_num][line_num][current_number_class][1] += 1;
            }
        }
    }
}
void Training::UpdateAllProbabilities() {
    for (int char_num = 0; char_num < IMAGE_SIZE; char_num++) {
        for (int line_num = 0; line_num < IMAGE_SIZE; line_num++) {
            for (int num_class = 0; num_class < NUM_CLASSES; num_class++) {
                CalculateProbabilityAt(char_num, line_num, num_class);
            }
        }
    }
}
void Training::CalculateProbabilityAt(int row, int col, int num_class) {
    int temp_count_unshaded = model.probs[row][col][num_class][0];
    int temp_count_shaded = model.probs[row][col][num_class][1];
    int temp_train_example_count = temp_count_unshaded + temp_count_shaded;
    double prob_unshaded = ((double)(k + temp_count_unshaded))/((double)(2*k + temp_train_example_count));
    double prob_shaded = 1 - prob_unshaded;
    model.probs[row][col][num_class][0] = prob_unshaded;
    model.probs[row][col][num_class][1] = prob_shaded;
}

void Training::OutputProbabilities() {
    std::ofstream outfile("training-data.txt");
    outfile << model;
}