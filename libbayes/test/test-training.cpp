#include "training-model.h"
#include "catch.hpp"

TEST_CASE("Constructor for classification testing file initializes file path properly") {
    Validate validator_test = Validate(testing_file);
    REQUIRE(validator_test.GetImagesFile() == testing_file);
}