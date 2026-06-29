#pragma once

#include <string_view>

#include <Image/Image.h>
#include <Rules/Rules.h>

struct ImageSerializer
{
    static void SaveImageFile(const Image& img, std::string_view path, ImageType type);

    static std::string_view CanonicalizeType(ImageType type);
};