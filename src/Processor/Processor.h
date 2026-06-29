#pragma once

#include <Image/Image.h>

class Processor {
    Image m_img{};
    
    CGColorSpaceRef m_colorSpace{};
    CGInterpolationQuality m_interpolation{};
    CGImageAlphaInfo m_alphaInfo{};
    size_t m_bitsPerComponent{};
    size_t m_bitsPerPixel{};
    size_t m_bytesPerRow{};
public:
    Processor(Image && img);
    ~Processor();

    Processor& SetColorSpace(CFStringRef colorspaceName);
    Processor& SetInterpolationQuality(CGInterpolationQuality interpolation) {m_interpolation = interpolation; return *this;}
    Processor& NewWidthHeight(uint64_t width, uint64_t height);

    const Image& Finalize() { return m_img; }
};