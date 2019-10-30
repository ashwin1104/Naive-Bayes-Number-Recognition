#include "training-model.h"
#include <fstream>

Training::Training(std::string &training_images, std::string &training_labels) {
    training_images_file = training_images;
    training_labels_file = training_labels;
    model = Model();
    k = 2;
}

void Training::RunTraining() {
    int num_total_images = 0;
    std::ifstream infile(training_images_file);
    std::ifstream infile2(training_labels_file);

    // loops through each image
    while (ReadNextImage(infile) && SetNextClass(infile2)) {
        SetCurrentImage();
        UpdateCounts();
        num_total_images += 1;
    }

    infile.close();
    infile2.close();

    UpdatePriors(num_total_images);
    UpdateAllProbabilities();
    OutputProbabilities();
}
bool Training::ReadNextImage(std::ifstream &infile) {
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
bool Training::SetNextClass(std::ifstream &infile2) {
    std::string line;
    std::getline(infile2, line);
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

void Training::UpdateCounts() {
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

void Training::UpdatePriors(int num_images) {
    double num_images_for_class = 0;

    for (int num_class = 0; num_class < NUM_CLASSES; num_class++) {
        num_images_for_class = model.probs[0][0][num_class][0] + model.probs[0][0][num_class][1];
        model.priors.push_back(num_images_for_class/num_images);
    }

    for (double prior : model.priors) {
        std::cout << prior << " " << std::endl;
    }
};

void Training::OutputProbabilities() {
    std::ofstream outfile("/Users/ashwinsaxena/CLionProjects/"
                          "naive-numbers-ashwin1104/libbayes/src/training-data.txt");
    if (outfile.is_open())
    {
        outfile << *this;
        outfile.close();
    }
    else std::cout << "Unable to open file";
}