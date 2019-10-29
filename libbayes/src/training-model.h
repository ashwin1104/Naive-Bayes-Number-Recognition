#ifndef NAIVEBAYES_TRAINING_MODEL_H
#define NAIVEBAYES_TRAINING_MODEL_H

#endif //NAIVEBAYES_TRAINING_MODEL_H

#include <string>
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
    void CalculateProbabilityAt(int row, int col, int num_class, int temp_count_unshaded, int temp_count_shaded);
    void OutputProbabilities();
};

