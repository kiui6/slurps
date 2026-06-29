#include "Processor.h"

#include <iostream>
#include <stdexcept>

#include <Image/Validation.hpp>

Processor::Processor(Image && img)
 : m_img(std::move(img))
{
    std::string error;
    if(!ValidateImage(m_img, error)) {
        throw std::runtime_error("Input: " + error);
    }

    CGColorSpaceRef colorSpace = CGImageGetColorSpace(img);
    if(m_colorSpace) {
        CFStringRef csname = CGColorSpaceCopyName(colorSpace);
        m_colorSpace = CGColorSpaceCreateWithName(csname);
        CFRelease(csname);
    } else {
        m_colorSpace = CGColorSpaceCreateWithName(kCGColorSpaceSRGB);
    }

    m_interpolation = kCGInterpolationMedium;

    m_alphaInfo = CGImageGetAlphaInfo(m_img);

    m_bitsPerComponent = CGImageGetBitsPerComponent(m_img);
    m_bitsPerPixel = CGImageGetBitsPerPixel(m_img);
    m_bytesPerRow = CGImageGetBytesPerRow(m_img);
}

Processor::~Processor()
{
    if(m_colorSpace) CGColorSpaceRelease(m_colorSpace);
}

Processor &Processor::SetColorSpace(CFStringRef colorspaceName)
{
    if(m_colorSpace) CGColorSpaceRelease(m_colorSpace);

    m_colorSpace = CGColorSpaceCreateWithName(colorspaceName);
    
    return *this;
}

Processor &Processor::NewWidthHeight(uint64_t width, uint64_t height)
{
    if(!m_img) {
        throw std::runtime_error("NewWidthHeight: underlying image is NULL!");
    }

    if(!m_colorSpace) {
        throw std::runtime_error("NewWidthHeight: invalid color space!");
    }

    CGContextRef ctx = CGBitmapContextCreate(NULL, 
        width, height, m_bitsPerComponent, 0, 
        m_colorSpace, kCGImageAlphaPremultipliedFirst);
    if(!ctx) {
        throw std::runtime_error("NewWidthHeight: Failed to create bitmap context!\n");
    }
        
    CGContextSetInterpolationQuality(ctx, m_interpolation);
    CGContextDrawImage(ctx, CGRectMake(0, 0, width, height), m_img);
    
    CGImageRef newImage = CGBitmapContextCreateImage(ctx);
    CGContextRelease(ctx);
    
    m_img = newImage;
    
    std::string error;
    if(!ValidateImage(m_img, error)) {
        throw std::runtime_error("NewWidthHeight: " + error);
    }
    
    return *this;
}