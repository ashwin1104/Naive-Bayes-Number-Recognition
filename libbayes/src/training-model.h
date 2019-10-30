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
    // constructor
    Training(std::string &training_images, std::string &training_labels);

    // main engine for training the model
    void RunTraining();

    // reads from image_path to get the IMAGE_SIZE length string defining the image
    bool ReadNextImage(std::ifstream &infile);

    // reads from training_labels_file to get the class corresponding to the current image
    bool SetNextClass(std::ifstream &infile2);

    // uses raw string from ReadNextImage to create an image object that handles the same information nicely
    void SetCurrentImage();

    // updates the counts of shaded and unshaded pixels for each pixel given the class
    void UpdateCounts();

    // engine for updating all the probabilities of pixels being shaded or unshaded
    void UpdateAllProbabilities();

    // updates the probability of a given pixel being shaded or unshaded given the class
    void CalculateProbabilityAt(int row, int col, int num_class);

    // updates the probabilities of each class being chosen given an image
    void UpdatePriors(int num_images);

    // outputs all probabilities and priors to a file
    void OutputProbabilities();

    // overloaded ofstream operator to output model.probs data to a file
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

