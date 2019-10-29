#include <image.hpp>
#include <iostream>
#include "training-model.h"

int main(int argc, char *argv[]) {
    std::string training_images_file;
    std::string training_labels_file;
    std::string testing_images_file = argv[0];
    std::string testing_labels_file = argv[1];
    Training trainer = Training(training_images_file, training_labels_file);
    // get file paths and update training model
}