#ifndef NAIVEBAYES_TRAINING_MODEL_H
#define NAIVEBAYES_TRAINING_MODEL_H

#endif //NAIVEBAYES_TRAINING_MODEL_H

#include <string>
#include <iostream>
#include <fstream>
#include "image.hpp"
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
    bool ReadNextImage();
    bool SetNextClass();
    void SetCurrentImage();
    void UpdateProbs();
    void UpdateAllProbabilities();
    void CalculateProbabilityAt(int row, int col, int num_class);
    void OutputProbabilities();
    friend std::ofstream &operator<<(std::ofstream &out, Model &model) {
        double temp_unshaded;
        double temp_shaded;
        for (int char_num = 0; char_num < IMAGE_SIZE; char_num++) {
            for (int line_num = 0; line_num < IMAGE_SIZE; line_num++) {
                for (int num_class = 0; num_class < NUM_CLASSES; num_class++) {
                    temp_unshaded = model.probs[char_num][line_num][num_class][0];
                    temp_shaded = model.probs[char_num][line_num][num_class][1];
                    out << temp_unshaded << " " << temp_shaded << std::endl;
                }
            }
        }
        return out;
    }
};

