#pragma once

#include <string_view>

#include <CoreGraphics/CoreGraphics.h>
#include <ImageIO/ImageIO.h>
#include <CoreFoundation/CoreFoundation.h>

class Image {
    CGImage* m_ref{};
public:
    Image() = default;
    explicit Image(CGImage* img) : m_ref(img) {}
    explicit Image(const char* path) {Load(path);}
    explicit Image(std::string_view path) {Load(path);}

    Image(Image&& other) noexcept {
        if (this != &other) {
            if (m_ref) {
                Release();
            }
            m_ref = other.m_ref;
            other.m_ref = nullptr;
        }
    }
    Image(const Image&) = delete;

    ~Image() {
        if (m_ref) {
            Release();
        }
        m_ref = nullptr;
    }
    
    void Load(std::string_view path);
    
    operator CGImage*() const {return m_ref;}
    CGImageRef Get() const { return m_ref; }

    inline bool IsValidDimensions() const {return m_ref ? (CGImageGetWidth(m_ref) && CGImageGetHeight(m_ref)) : false;}
    inline bool IsValidComponents() const {return m_ref ? CGImageGetBitsPerComponent(m_ref) : false;}
    inline bool IsValidBitsPerPixel() const {return m_ref ? CGImageGetBitsPerPixel(m_ref) : false;}
    inline bool IsValidBitsPerRow() const {return m_ref ? CGImageGetBytesPerRow(m_ref) : false;}
    inline bool IsValidColorSpace() const {return m_ref ? CGImageGetColorSpace(m_ref) != nullptr : false;}
    inline bool IsValidDataProvider() const {return m_ref ? CGImageGetDataProvider(m_ref) != nullptr : false;}

    operator bool () const {return m_ref != nullptr;}

    Image& operator=(const Image&) = delete;
    
    Image& operator=(Image&& other) noexcept {
        if (this != &other) {
            if (m_ref) {
                Release();
            }
            m_ref = other.m_ref;
            other.m_ref = nullptr;
        }
        return *this;
    }

    Image& operator=(CGImage* img) noexcept {
        if (img != m_ref) {
            if (m_ref) {
                Release();
            }
            m_ref = img;
        }
        return *this;
    }

private:
    inline void Release() {CGImageRelease(m_ref);}
};