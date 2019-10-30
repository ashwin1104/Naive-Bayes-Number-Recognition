#ifndef NAIVEBAYES_TRAINING_MODEL_H
#define NAIVEBAYES_TRAINING_MODEL_H

#endif //NAIVEBAYES_TRAINING_MODEL_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "model.hpp"

class Training {
private:
    std::string raw_image;
    Image current_image;
    Model model;
    int current_number_class;
    int k;
    std::string training_images_file;
    std::string training_labels_file;
public:
    Training(std::string &training_images, std::string &training_labels);
    void RunTraining();
    bool ReadNextImage(std::ifstream &infile);
    bool SetNextClass(std::ifstream &infile2);
    void SetCurrentImage();
    void UpdateProbs();
    void UpdateAllProbabilities();
    void CalculateProbabilityAt(int row, int col, int num_class);
    void UpdatePriors(int num_images);
    void OutputProbabilities();
    friend std::ofstream &operator<<(std::ofstream &out, Training &trainer) {
        double temp_unshaded;
        double temp_shaded;
        for (auto & prob : trainer.model.probs) {
            for (auto & line_num : prob) {
                for (auto & num_class : line_num) {
                    temp_unshaded = num_class[0];
                    temp_shaded = num_class[1];
                    std::cout << temp_unshaded << " " << temp_shaded << std::endl;
                    out << temp_unshaded << " " << temp_shaded << std::endl;
                }
            }
        }
        for (double prior : trainer.model.priors) {
            std::cout << prior << " " << std::endl;
            out << prior << " " << std::endl;
        }
        return out;
    }
};

