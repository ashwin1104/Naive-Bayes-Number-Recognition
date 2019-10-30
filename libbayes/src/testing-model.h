#include <string>
#include "model.hpp"
#include <math.h>
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
    Tester(std::string &image_file_path, std::string &label_file_path, std::string &probabilities_file_path);
    void RunTester();
    bool SetNextClass(std::ifstream &infile2);
    bool ReadNextImage(std::ifstream &infile);
    void SetCurrentImage();
    void UpdateProbs(std::ifstream &infile3);
    void SplitString(std::string &line);
    void InitializeClassProbs();
    void UpdateProbForClass(int num_class, bool isShaded);
    void UsePriors(std::ifstream &infile3);
    double CalculateAccuracy(int num_correct, int num_total);
    void UpdateWinningDigit();
};