#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <memory>

#include "Types.h"
#include "ProcessingOperation.h"

struct Rules {
    std::vector<std::string> inputs;
    std::string output;
    
    ImageType inputType = ImageType::PNG;
    ImageType outputType = ImageType::PNG;

    std::vector<std::unique_ptr<ProcessingOperation>> processingOperations;

};