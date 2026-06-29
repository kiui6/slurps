#pragma once

#include "Rules.h"
#include <ArgParser.h>

static inline bool ParseRules(const ArgParser& args, Rules& rules, std::string& error) {
    if(args.GetInputs().size() == 0) {
        error = "No input files.";
        return false;
    }

    rules.inputs = std::move(args.GetInputs());
    
    if(!args.Has("output")) {
        error = "No output template provided.";
        return false;
    }

    rules.output = *args.Get("output");

    auto outputTypeStr = args.Get("format");
    if(outputTypeStr) {
        if(*outputTypeStr == "png"){
            rules.outputType = ImageType::PNG; 
        } else if(*outputTypeStr == "jpg" || *outputTypeStr == "jpeg"){
            rules.outputType = ImageType::JPEG; 
        } else if(*outputTypeStr == "icns"){
            rules.outputType = ImageType::ICNS; 
        } else {
            error = "Unsupported output format.";
            return false;
        }
    } else {
        // TODO: Try deduce from extension or default to input's format
    }
    
    return true;
}