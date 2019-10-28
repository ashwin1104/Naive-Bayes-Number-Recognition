#pragma once

#include <cstdlib>

/*
 * We've given you a starter class to represent an image.
 * You are totally allowed to delete, change, move, rename, etc. this class
 * however you like! In fact, we encourage it! It only exists as a starting
 * point of reference.
 *
 * You can delete this comment once you're done with it.
 */

constexpr size_t IMAGE_SIZE = 28;

class Image {
private:
    char pixels[IMAGE_SIZE][IMAGE_SIZE];
};
