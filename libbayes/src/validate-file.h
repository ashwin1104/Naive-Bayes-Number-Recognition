#include <string>
#include <set>
#ifndef NAIVEBAYES_VALIDATE_FILE_H
#define NAIVEBAYES_VALIDATE_FILE_H

#endif //NAIVEBAYES_VALIDATE_FILE_H
class Validate {
private:
    std::string images_file_path;
    std::string labels_file_path;
    int image_num_lines;
    int label_num_lines;
    std::set<char> valid_image_chars;
    std::set<char> valid_label_chars;
public:
    // constructors
    Validate(std::string &images);
    Validate(std::string &images, std::string &labels);

    // engine for validating image
    bool ValidateImage();

    // engine for validating label
    bool ValidateLabel();

    // makes sure character type is valid for each line of each image
    bool ValImageTypeChars(std::string &line);

    // makes sure the number of characters is valid for each line of each image
    bool ValImageNumCharsInLine(std::string &line);

    // makes sure the number of lines is valid for each image
    bool ValImageNumLines();

    // makes sure character type (digit) is valid for each label
    bool ValLabelTypeChars(std::string &line);

    // makes sure the number of characters is valid (1) for each label
    bool ValLabelNumChars(std::string &line);

    // makes sure the number of lines in label file is exactly 28 times as small as the number of lines in image file
    bool ValLabelNumLines();

    // initializers for the valid_image_chars and valid_label_chars vectors
    void SetValImageChars();
    void SetValLabelChars();

    // getters
    std::string GetImagesFile();
    std::string GetLabelsFile();
};
