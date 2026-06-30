#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <memory>

#include "Types.h"
#include <Processor/ProcessingOperation.h>

struct Rules {
    std::vector<std::string> inputs;
    std::string output;
    
    ImageType inputType = ImageType::Auto;
    ImageType outputType = ImageType::Auto;

    ResampleMode ResampleMode = ResampleMode::Bilinear;

    std::vector<std::unique_ptr<ProcessingOperation>> processingOperations;

};