#include <iostream>

#include <CoreGraphics/CoreGraphics.h>
#include <ImageIO/ImageIO.h>
#include <CoreFoundation/CoreFoundation.h>

#include "Image/Image.h"
#include "ArgParser.h"
#include "Processor/Processor.h"
#include "Serializer/Serializer.h"
#include "Rules/Rules.h"
#include "Rules/Validator.h"
#include "Rules/RulesParsing.hpp"

static CGImageRef resize_nearest(CGImageRef src, size_t newW, size_t newH) {
    CGColorSpaceRef cs = CGColorSpaceCreateWithName(kCGColorSpaceSRGB);
    CGContextRef ctx = CGBitmapContextCreate(NULL, newW, newH, 8, newW * 4, cs, kCGImageAlphaPremultipliedLast);
    CGColorSpaceRelease(cs);
    if (!ctx) return NULL;

    
    
    CGContextSetInterpolationQuality(ctx, kCGInterpolationNone);
    CGContextDrawImage(ctx, CGRectMake(0, 0, newW, newH), src);
    
    CGImageRef dst = CGBitmapContextCreateImage(ctx);
    CGContextRelease(ctx);
    return dst;
}

void PrintUsage() {
    std::cerr << "usage: slurps <Inputs> --output <Path> [-flags] [--argument <value>]\n\n";
    std::cerr << "\t--resample-mode <nearest/bilinear> - Specify resampling mode for operations\n\n";
    std::cerr << "\t--newWidthHeight <Width>:<Height> - Change width & height of an image\n\n";
    std::cerr << "\t--output <Path> - Path for the output file. Available templates:\n\n";
    std::cerr << "\t\t<Counter> - A counter number increasing with each processed file.\n";
}

int main(int argc, char* argv[])
{
    ArgParser args(argc, argv);

    Rules rules{};
    std::string error;
    if(!ParseRules(args, rules, error)) {
        std::cerr << error << "\n";
        PrintUsage();
        return 1;
    }

    
    for(const std::string& inputPath : rules.inputs) {
        try {
            // TODO: Resolve output template
            std::string outputPath = rules.output;
            std::cout << inputPath << " -> " << outputPath;

            // Load image
            Image img(inputPath);
            
            // Process
            Processor processor(std::move(img));

            const Image& result = processor
                .SetInterpolationQuality(kCGInterpolationNone)
                .NewWidthHeight(128, 128)
                .Finalize();

            // Save to disk
            ImageSerializer::SaveImageFile(result, outputPath, rules.outputType);
            std::cout << " [OK]\n";
        } catch(const std::runtime_error& exc) {
            std::cout << " [FAILED]\n";
            std::cerr << exc.what() << "\n";
            return -1;
        }
    }

    return 0;
}