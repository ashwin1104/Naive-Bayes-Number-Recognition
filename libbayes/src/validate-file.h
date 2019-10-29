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
    Validate(std::string &images);
    Validate(std::string &images, std::string &labels);
    bool ValidateImage();
    bool ValidateLabel();
    bool ValImageNumLines();
    bool ValImageNumCharsInLine(std::string &line);
    bool ValImageTypeChars(std::string &line);
    bool ValLabelTypeChars(std::string &line);
    bool ValLabelNumChars(std::string &line);
    bool ValLabelNumLines();
    void SetValImageChars();
    void SetValLabelChars();
};
