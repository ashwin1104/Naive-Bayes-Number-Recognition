#include <fstream>
#include "testing-model.h"
#include "catch.hpp"

std::string these_images =
        "/Users/ashwinsaxena/CLionProjects/naive-numbers-ashwin1104/libbayes/"
        "test/resources/digitdata/testimages";
std::string these_labels =
        "/Users/ashwinsaxena/CLionProjects/naive-numbers-ashwin1104/libbayes/"
        "test/resources/digitdata/testlabels";

// ReadNextImage
TEST_CASE("Ensures ReadNextImage properly stores raw image data !") {
    Tester tester = Tester(these_images, these_labels);
    std::ifstream infile(these_images);
    tester.ReadNextImage(infile);
    REQUIRE(tester.GetRawImage() == "                                                                                                                                                                                                                 ++###+                      ######+                    +######+                    ##+++##+                   +#+  +##+                   +##++###+                   +#######+                   +#######+                    +##+###                       ++##+                       +##+                        ###+                      +###+                       +##+                       +##+                       +##+                       +##+                        ##+                        +#+                         +#+                                             ");
}

// SetNextClass
TEST_CASE("Ensures SetNextClass properly stores the class corresponding to the next image !") {
    Tester tester = Tester(these_images, these_labels);
    std::ifstream infile(these_labels);
    tester.SetCurrentClass(infile);
    REQUIRE(tester.GetCurrentClass() == 9);
}

// UpdateProbs
TEST_CASE("Ensures all log probabilities are less than 0") {
    Tester tester = Tester(these_images, these_labels);
    std::ifstream infile(these_images);
    std::ifstream infile2("/Users/ashwinsaxena/CLionProjects/"
                          "naive-numbers-ashwin1104/libbayes/src/training-data.txt");
    tester.InitializeClassProbs();
    tester.ReadNextImage(infile);
    tester.SetCurrentImage();
    tester.UpdateProbs(infile2);
    bool is_prob_valid = true;
    for (int num_class = 0; num_class < NUM_CLASSES; num_class++) {
        if (tester.class_probabilities[num_class] >= 0) {
            is_prob_valid = false;
        }
    }
    REQUIRE(is_prob_valid);
}