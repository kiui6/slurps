#include "Image.h"

void Image::Load(std::string_view path)
{
    if(m_ref) CFRelease(m_ref);

    CFURLRef url = CFURLCreateFromFileSystemRepresentation(NULL, (const UInt8*)path.data(), path.size(), false);
    if (!url) return;

    CGImageSourceRef source = CGImageSourceCreateWithURL(url, NULL);
    CFRelease(url);
    if (!source) return;

    m_ref = CGImageSourceCreateImageAtIndex(source, 0, NULL);
    CFRelease(source);
}