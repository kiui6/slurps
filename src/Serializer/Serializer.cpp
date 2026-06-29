#include "Serializer.h"

#include <Image/Validation.hpp>

#include <stdexcept>

void ImageSerializer::SaveImageFile(const Image &img, std::string_view path, ImageType type)
{
    std::string error;
    if(!ValidateImage(img, error)) {
        throw std::runtime_error("SaveImageFile: " + error);
    }

    CFURLRef url = CFURLCreateFromFileSystemRepresentation(NULL, (const UInt8*)path.data(), path.size(), false);
    if (!url) {
        throw std::runtime_error("SaveImageFile: Failed to create URL");
    }
    
    CGImageDestinationRef dest = CGImageDestinationCreateWithURL(url, CFStringCreateWithCString(NULL, CanonicalizeType(type).data(), kCFStringEncodingUTF8), 1, NULL);
    CFRelease(url);
    if (!dest) {
        throw std::runtime_error("SaveImageFile: Failed to create URL");
    }

    CGImageDestinationAddImage(dest, img, NULL);

    bool success = CGImageDestinationFinalize(dest);
    CFRelease(dest);

    if(!success) {
        throw std::runtime_error("SaveImageFile: Failed saving file to the disk");
    }
}

std::string_view ImageSerializer::CanonicalizeType(ImageType type)
{
    switch(type)
    {
        case ImageType::PNG:
            return "public.png";
        case ImageType::JPEG:
            return "public.jpeg";
        case ImageType::ICNS:
            return "com.apple.icns";
        default:
            return "";
    }
}
