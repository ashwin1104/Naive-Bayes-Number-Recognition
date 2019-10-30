#include <string>
#include "model.hpp"
#include <cmath>
#include <cfloat>
#include <iostream>
#ifndef NAIVEBAYES_TESTING_MODEL_H
#define NAIVEBAYES_TESTING_MODEL_H

#endif //NAIVEBAYES_TESTING_MODEL_H

class Tester {
private:
    std::string image_path;
    std::string label_path;
    std::string probabilities_path;
    std::string raw_image;
    double current_unshaded_prob;
    double current_shaded_prob;
    int correct_class;
    Image current_image;
    double class_probabilities[NUM_CLASSES];
    int winning_digit;
public:
    // constructor
    Tester(std::string &image_file_path, std::string &label_file_path);

    // main engine for testing the model
    void RunTester();

    // reads from image_path to get the IMAGE_SIZE length string defining the image
    bool ReadNextImage(std::ifstream &infile);

    // reads from label_path to get the class corresponding to the current image
    bool SetNextClass(std::ifstream &infile2);

    // uses raw string from ReadNextImage to create an image object that handles the same information nicely
    void SetCurrentImage();

    // engine for updating the posterior probabilities based on the image's shade value at each pixel
    void UpdateProbs(std::ifstream &infile3);

    // splits line from probability_path into two doubles (one for shaded prob, one for unshaded prob)
    void SplitString(std::string &line);

    // sets or resets class_probabilities to 0
    void InitializeClassProbs();

    // updates posterior probability for a single class for a single pixel based on if the pixel is shaded or not
    void UpdateProbForClass(int num_class, bool isShaded);

    // finalizes posterior probabilities for all classes by adding the prior probabilities
    void UsePriors(std::ifstream &infile3);

    // calculates accuracy of the model based on the images classified
    double CalculateAccuracy(int num_correct, int num_total);

    // sets the winning digit based on the highest posterior probability (max function)
    void UpdateWinningDigit();
};