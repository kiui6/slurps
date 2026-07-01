#pragma once

#include <string>
#include <cstdint>

#include <Image/Image.h>

class PatternExpander
{
public:
    static inline std::string Expand(
        const std::string& pattern,
        const std::string& inputPath,
        uint64_t index,
        uint64_t width,
        uint64_t height) 
    {
        std::string result = pattern;
        size_t pos = 0;

        std::string inputFilename;
        size_t lastInputSlashPos = inputPath.find_last_of("/");
        if(lastInputSlashPos == std::string::npos) {
            lastInputSlashPos = inputPath.find_last_of("\\");
            if(lastInputSlashPos == std::string::npos) {
                inputFilename = inputPath;
            }
        }

        if(lastInputSlashPos != std::string::npos) {
            inputFilename = pattern.substr(lastInputSlashPos + 1);
        }

        std::string inputBasename, inputExtension;

        if((pos = inputFilename.find(".")) != std::string::npos) {
            inputBasename = inputFilename.substr(0, pos);
            inputExtension = inputFilename.substr(pos+1);
        } else {
            inputBasename = inputFilename;
        }

        if ((pos = result.find("<INDEX>")) != std::string::npos) {
            result.replace(pos, 7, std::to_string(index));
        }

        if ((pos = result.find("<BASENAME>")) != std::string::npos) {
            result.replace(pos, 10, std::to_string(inputBasename));
        }

        if ((pos = result.find("<EXT>")) != std::string::npos) {
            result.replace(pos, 5, std::to_string(inputExtension));
        }

        return pattern;
    }
};