#include "training-model.h"
#include "testing-model.h"
#include "validate-file.h"

int main(int argc, char* argv[]) {
    std::string training_images_file;
    std::string training_labels_file;
    std::string testing_images_file;
    std::string testing_labels_file;
    std::string probabilities_file;
    if (argc == 1) {
        return 0;
    }
    std::string command = argv[1];
    if (command == "--t") {
        if (argc < 3) {
            return 0;
        }
        // get file paths and update training model
        training_images_file = argv[2];
        training_labels_file = argv[3];
        Validate validator = Validate(training_images_file, training_labels_file);
        if (validator.ValidateImage() && validator.ValidateLabel()) {
            Training trainer = Training(training_images_file, training_labels_file);
            trainer.RunTraining();
        }
    }
    else if (command == "--c") {
        if (argc < 4) {
            return 0;
        }
        // get file path and test out classification model
        testing_images_file = argv[2];
        testing_labels_file = argv[3];
        probabilities_file = argv[4];
        Validate validator = Validate(testing_images_file);
        if (validator.ValidateImage()) {
            Tester tester = Tester(testing_images_file, testing_labels_file, probabilities_file);
            tester.RunTester();
        }
    }
    return 0;
}