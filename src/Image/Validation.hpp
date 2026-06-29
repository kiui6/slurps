#pragma once

#include "Image.h"
#include <optional>
#include <string>

// Returns error string
static bool ValidateImage(const Image& image, std::string& error) {
    if (!image) {
        error = std::string("CGImageRef == nullptr");
        return false;
    }

    if (!image.IsValidDimensions()) {
        error = std::string("Invalid dimensions");
        return false;
    }

    if (!image.IsValidComponents()) {
        error = std::string("Invalid components");
        return false;
    }

    if (!image.IsValidBitsPerPixel()) {
        error = std::string("Invalid BPP");
        return false;
    }

    if (!image.IsValidBitsPerRow()) {
        error = std::string("Invalid BPR");
        return false;
    }

    if (!image.IsValidColorSpace()) {
        error = std::string("Invalid color space");
        return false;
    }

    if (!image.IsValidDataProvider()) {
        error = std::string("Invalid image data provider");
        return false;
    }

    return true;
}