#include "training-model.h"
#include "catch.hpp"

std::string images =
        "/Users/ashwinsaxena/CLionProjects/naive-numbers-ashwin1104/libbayes/"
        "test/resources/digitdata/trainingimages";
std::string labels =
        "/Users/ashwinsaxena/CLionProjects/naive-numbers-ashwin1104/libbayes/"
        "test/resources/digitdata/traininglabels";

// ReadNextImage
TEST_CASE("Ensures ReadNextImage properly stores raw image data") {
    Training trainer = Training(images, labels);
    std::ifstream infile(images);
    trainer.ReadNextImage(infile);
    REQUIRE(trainer.GetRawImage() ==   "                                                                              "
                                       "                                                                              "
                                       "+++++##+            +++++######+###+           +##########+++++             ##"
                                       "#####+##                  +++###  ++                     +#+                  "
                                       "       +#+                          +#+                         +##++         "
                                       "               +###++                       ++##++                        +##+"
                                       "                         ###+                     +++###                    ++"
                                       "#####+                  ++######+                 ++######+                  +"
                                       "######+                 ++######+                   +####++                   "
                                       "                                                                              "
                                       "    ");
}

// SetNextClass
TEST_CASE("Ensures SetNextClass properly stores the class corresponding to the next image") {
    Training trainer = Training(images, labels);
    std::ifstream infile(labels);
    trainer.SetCurrentClass(infile);
    REQUIRE(trainer.GetCurrentClass() == 5);
}

// UpdateCounts
TEST_CASE("Ensures UpdateCounts properly updates the shaded and unshaded counts for each pixel") {
    Training trainer = Training(images, labels);
    std::ifstream infile(images);
    trainer.ReadNextImage(infile);
    trainer.SetCurrentImage();
    trainer.UpdateCounts();
    bool is_updated_correctly = true;
    for (int char_num = 0; char_num < IMAGE_SIZE; char_num++) {
        for (int line_num = 0; line_num < IMAGE_SIZE; line_num++) {
            if (trainer.model.probs[char_num][line_num][trainer.GetCurrentClass()][0] +
            trainer.model.probs[char_num][line_num][trainer.GetCurrentClass()][1] != 1) {
                is_updated_correctly = false;
            }
        }
    }
    REQUIRE(is_updated_correctly);
}

// UpdateAllProbabilities
TEST_CASE("Ensures all probabilities are between 0 and 1") {
    Training trainer = Training(images, labels);
    std::ifstream infile(images);
    trainer.ReadNextImage(infile);
    trainer.SetCurrentImage();
    trainer.UpdateCounts();
    trainer.UpdateAllProbabilities();
    bool is_prob_valid = true;
    for (int char_num = 0; char_num < IMAGE_SIZE; char_num++) {
        for (int line_num = 0; line_num < IMAGE_SIZE; line_num++) {
            for (int num_class = 0; num_class < NUM_CLASSES; num_class++) {
                if (!(trainer.model.probs[char_num][line_num][num_class][0] < 1 &&
                trainer.model.probs[char_num][line_num][num_class][0] > 0 &&
                trainer.model.probs[char_num][line_num][num_class][1] < 1 &&
                trainer.model.probs[char_num][line_num][num_class][1] > 0)) {
                    is_prob_valid = false;
                }
            }
        }
    }
    REQUIRE(is_prob_valid);
}

// UpdatePriors
TEST_CASE("Ensures all priors are between 0 and 1 (inclusive)") {
    Training trainer = Training(images, labels);
    std::ifstream infile(images);
    trainer.ReadNextImage(infile);
    trainer.SetCurrentImage();
    trainer.UpdateCounts();
    trainer.UpdatePriors(1);
    bool is_prob_valid = true;
    for (int num_class = 0; num_class < NUM_CLASSES; num_class++) {
        if (!(trainer.model.priors[num_class] <= 1 &&
        trainer.model.priors[num_class] >= 0)) {
            is_prob_valid = false;
        }
    }
    REQUIRE(is_prob_valid);
}