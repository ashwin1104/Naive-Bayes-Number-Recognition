#include "image.hpp"
#include "catch.hpp"

// Tests the ParseImage function
TEST_CASE("Given a valid image as a raw string, ParseImage should input a value of 1 or 0 for the image's 2d array") {
    Image image = Image();
    std::string raw_image = "                                                                                    "
                            "                                                                        +++++##+    "
                            "        +++++######+###+           +##########+++++             #######+##          "
                            "        +++###  ++                     +#+                         +#+              "
                            "            +#+                         +##++                        +###++         "
                            "              ++##++                        +##+                         ###+       "
                            "              +++###                    ++#####+                  ++######+         "
                            "        ++######+                  +######+                 ++######+               "
                            "    +####++                                                                         "
                            "                            ";
    image.ParseImage(raw_image);
    bool is_parsed;
    for (int row = 0; row < IMAGE_SIZE; row++) {
        for (int col = 0; col < IMAGE_SIZE; col++) {
            if (image.GetImagePixelAt(row, col) != 0 && image.GetImagePixelAt(row, col) != 1) {
                is_parsed = false;
            }
        }
    }
    is_parsed = true;
    REQUIRE(is_parsed);
}