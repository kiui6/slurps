#include "Validator.h"

bool RulesValidator::ValidateICNS(const Rules &rules, std::string &error)
{
    if(rules.NewWidthHeight.outputWidth != rules.NewWidthHeight.outputHeight) {
        error = "ICNS image dimensions must be same.";
        return false;
    }

    if(!(rules.NewWidthHeight.outputWidth != 16 ||
        rules.NewWidthHeight.outputWidth != 32 ||
        rules.NewWidthHeight.outputWidth != 128 ||
        rules.NewWidthHeight.outputWidth != 256 ||
        rules.NewWidthHeight.outputWidth != 512 ||
        rules.NewWidthHeight.outputWidth != 1024)) {
        error = std::string("Unsupported ICNS dimesions.\n") 
            + "Supported dimensions: \n"
            + "\t16x16 @1\n"
            + "\t32x32 @1\n"
            + "\t64x64 @2\n"
            + "\t128x128 @1\n"
            + "\t256x256 @1\n"
            + "\t512x512 @1\n"
            + "\t1024x1024 @2";
        return false;
    }

    return true;
}

bool RulesValidator::Validate(const Rules &rules, std::string &error)
{
    if(rules.outputType == ImageType::ICNS)
    if(!ValidateICNS(rules, error)) {
        return false;
    }

    return true;
}