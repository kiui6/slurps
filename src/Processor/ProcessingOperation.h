#pragma once

#include <Types.h>

#include <cstdint>

enum class ProcessingOpType {
    None,
    NewWidthHeight,
};

struct ProcessingOperation {
    ProcessingOpType type;

    ProcessingOperation(ProcessingOpType op) : type(op) {}
};

struct NewWidthHighProcessingOperation : public ProcessingOperation {
    NewWidthHighProcessingOperation() : ProcessingOperation(ProcessingOpType::NewWidthHeight) {}

    uint64_t outputWidth = 0, outputHeight = 0;
    ResampleMode ResampleMode = ResampleMode::Bilinear;
};