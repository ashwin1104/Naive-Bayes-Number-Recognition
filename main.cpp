#include "training-model.h"
#include "testing-model.h"
#include "validate-file.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        return 0;
    }

    std::string command = argv[1];
    std::string images_file = argv[2];
    std::string labels_file = argv[3];

    Validate validator = Validate(images_file, labels_file);
    if (!(validator.ValidateImage() && validator.ValidateLabel())) {
        return 0;
    }

    // --t means training
    if (command == "--t") {
        // update training model
        Training trainer = Training(images_file, labels_file);
        trainer.RunTraining();
    }
    // --c means classification (testing)
    else if (command == "--c") {
        // test out classification model
        Tester tester = Tester(images_file, labels_file);
        tester.RunTester();
    }
    return 0;
}