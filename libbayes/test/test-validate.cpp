#include "validate-file.h"
#include "catch.hpp"
#include <iostream>
#include <fstream>

std::string testing_file =
        "Users/ashwinsaxena/CLionProjects/naive-numbers-ashwin1104/libbayes/test/resources/digitdata/testimages";
std::string training_images =
        "/Users/ashwinsaxena/CLionProjects/naive-numbers-ashwin1104/libbayes/"
        "test/resources/digitdata/trainingimages";
std::string training_labels =
        "/Users/ashwinsaxena/CLionProjects/naive-numbers-ashwin1104/libbayes/"
        "test/resources/digitdata/traininglabels";

// Constructors
TEST_CASE("Constructor for classification testing file initializes file path properly") {
    Validate validator_test = Validate(testing_file);
    REQUIRE(validator_test.GetImagesFile() == testing_file);
}
TEST_CASE("Constructor for training files initializes file paths properly") {
    Validate validator_train = Validate(training_images, training_labels);
    REQUIRE(validator_train.GetLabelsFile() == training_labels);
    REQUIRE(validator_train.GetImagesFile() == training_images);
}

// ValidateImage
TEST_CASE("Returns true when file path is valid for an image format") {
    Validate validator_train = Validate(training_images, training_labels);
    REQUIRE(validator_train.ValidateImage());
}
TEST_CASE("Returns false when file path is NOT valid for an image format") {
    std::string file_path = "hi";
    Validate invalidator = Validate(file_path);
    REQUIRE_FALSE(invalidator.ValidateImage());
}

// ValidateLabel
TEST_CASE("Returns true when file path is valid for a label format") {
    Validate validator_train = Validate(training_images, training_labels);
    validator_train.ValidateImage();
    REQUIRE(validator_train.ValidateLabel());
}
TEST_CASE("Returns false when file path is NOT valid for a label format") {
    std::string file_path = "hi";
    Validate invalidator = Validate(file_path);
    REQUIRE_FALSE(invalidator.ValidateLabel());
}

// ValImageNumLines
TEST_CASE("Returns true when file length is a multiple of IMAGE_SIZE") {
    Validate validator_train = Validate(training_images, training_labels);
    REQUIRE(validator_train.ValImageNumLines());
}
TEST_CASE("Returns false when file length is NOT a multiple of IMAGE_SIZE") {
    std::string file_path = "/Users/ashwinsaxena/CLionProjects/naive-numbers-ashwin1104/libbayes/src/invalid-num-lines";
    Validate invalidator = Validate(file_path);
    invalidator.ValidateImage();
    std::cout << invalidator.GetImagesFile() << std::endl;
    REQUIRE_FALSE(invalidator.ValImageNumLines());
}

// ValLabelNumLines
TEST_CASE("Returns true when label file length is the same as number of images in the image file") {
    Validate validator_train = Validate(training_images, training_labels);
    validator_train.ValidateImage();
    validator_train.ValidateLabel();
    REQUIRE(validator_train.ValLabelNumLines());
}
TEST_CASE("Returns false when label file length is NOT the same as number of images in the image file") {
    std::string file_labels = "/Users/ashwinsaxena/CLionProjects/"
                              "naive-numbers-ashwin1104/libbayes/src/invalid-label-num-lines";
    Validate invalidator = Validate(training_images, file_labels);
    invalidator.ValidateImage();
    invalidator.ValidateLabel();
    REQUIRE_FALSE(invalidator.ValLabelNumLines());
}

// ValImageNumChars
TEST_CASE("Returns true when number of characters for a given line of an image file path is IMAGE_SIZE") {
    Validate validator_train = Validate(training_images, training_labels);
    std::ifstream infile(training_images);
    std::string line;
    if (infile.is_open()) {
        std::getline(infile, line);
    }
    infile.close();
    REQUIRE(validator_train.ValImageNumCharsInLine(line));
}
TEST_CASE("Returns false when number of characters for a given line of an image file path is NOT IMAGE_SIZE") {
    std::string file_labels = "/Users/ashwinsaxena/CLionProjects/"
                              "naive-numbers-ashwin1104/libbayes/src/invalid-label-num-lines";
    Validate invalidator = Validate(file_labels, training_labels);
    std::ifstream infile(file_labels);
    std::string line;
    if (infile.is_open()) {
        std::getline(infile, line);
    }
    infile.close();
    REQUIRE_FALSE(invalidator.ValImageNumCharsInLine(line));
}

// ValLabelNumChars
TEST_CASE("Returns true when number of characters for a given line of a label file path is 1") {
    Validate validator_train = Validate(training_images, training_labels);
    std::ifstream infile(training_labels);
    std::string line;
    if (infile.is_open()) {
        std::getline(infile, line);
    }
    infile.close();
    REQUIRE(validator_train.ValLabelNumChars(line));
}
TEST_CASE("Returns false when number of characters for a given line of a label file path is NOT 1") {
    std::string file_path = "/Users/ashwinsaxena/CLionProjects/naive-numbers-ashwin1104/libbayes/src/invalid-num-lines";
    Validate invalidator = Validate(training_images, file_path);
    std::ifstream infile(file_path);
    std::string line;
    if (infile.is_open()) {
        std::getline(infile, line);
    }
    infile.close();
    REQUIRE_FALSE(invalidator.ValLabelNumChars(line));
}

// ValImageTypeChars
TEST_CASE("Returns true when all chars in a given line of an image file path are in valid_image_chars") {
    std::string file_path = "/Users/ashwinsaxena/CLionProjects/naive-numbers-ashwin1104/libbayes/src/invalid-num-lines";
    Validate validator_train = Validate(file_path, training_labels);
    validator_train.ValidateImage();
    std::ifstream infile(file_path);
    std::string line;
    if (infile.is_open()) {
        std::getline(infile, line);
    }
    infile.close();
    REQUIRE(validator_train.ValImageTypeChars(line));
}
TEST_CASE("Returns false when not all chars in a given line of an image file path are in valid_image_chars") {
    std::string file_labels = "/Users/ashwinsaxena/CLionProjects/"
                              "naive-numbers-ashwin1104/libbayes/src/invalid-label-num-lines";
    Validate invalidator = Validate(file_labels, training_labels);
    invalidator.ValidateImage();
    std::ifstream infile(file_labels);
    std::string line;
    if (infile.is_open()) {
        std::getline(infile, line);
    }
    infile.close();
    REQUIRE_FALSE(invalidator.ValImageTypeChars(line));
}
TEST_CASE("Returns false when the given line of the image file is empty") {
    std::string file_labels = "/Users/ashwinsaxena/CLionProjects/"
                              "naive-numbers-ashwin1104/libbayes/src/invalid-label-num-lines";
    Validate invalidator = Validate(file_labels, training_labels);
    invalidator.ValidateImage();
    std::string line;
    REQUIRE_FALSE(invalidator.ValImageTypeChars(line));
}

// ValLabelTypeChars
TEST_CASE("Returns true when the char in a given line of a label file path is in valid_label_chars") {
    Validate validator_train = Validate(training_images, training_labels);
    validator_train.ValidateLabel();
    std::ifstream infile(training_labels);
    std::string line;
    if (infile.is_open()) {
        std::getline(infile, line);
    }
    infile.close();
    REQUIRE(validator_train.ValLabelNumChars(line));
}
TEST_CASE("Returns false when the char in a given line of a label file path is NOT in valid_label_chars") {
    std::string file_path = "/Users/ashwinsaxena/CLionProjects/naive-numbers-ashwin1104/libbayes/src/invalid-num-lines";
    Validate invalidator = Validate(training_images, file_path);
    invalidator.ValidateLabel();
    std::ifstream infile(file_path);
    std::string line;
    if (infile.is_open()) {
        std::getline(infile, line);
    }
    infile.close();
    REQUIRE_FALSE(invalidator.ValLabelNumChars(line));
}
TEST_CASE("Returns false when the given line of the label file is empty") {
    std::string file_path = "/Users/ashwinsaxena/CLionProjects/naive-numbers-ashwin1104/libbayes/src/invalid-num-lines";
    Validate invalidator = Validate(training_images, file_path);
    invalidator.ValidateLabel();
    std::string line;
    REQUIRE_FALSE(invalidator.ValLabelNumChars(line));
}