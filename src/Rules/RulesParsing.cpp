#include "RulesParsing.h"

#include <charconv>

const std::unordered_map<std::string, bool (*)(const ArgParser::Argument&, Rules&, std::string&)> RuleParserList::m_list = {
    {"output", RuleParserList::ParseOutput},
    {"o", RuleParserList::ParseOutput},

    {"format", RuleParserList::ParseFormat},
    {"f", RuleParserList::ParseFormat},

    {"resampleMode", RuleParserList::ParseResampleMode},
    {"r", RuleParserList::ParseResampleMode},

    {"newWidthHeight", RuleParserList::ParseNewWidthHeight},
    {"z", RuleParserList::ParseNewWidthHeight},
};

bool RuleParserList::ParseOutput(const ArgParser::Argument &arg, Rules &rules, std::string &error)
{
    if(!arg.value.has_value()) {
        error = "No output path provided";
        return false;
    }
    rules.output = *arg.value;
    return true;
}

bool RuleParserList::ParseFormat(const ArgParser::Argument &arg, Rules &rules, std::string &error)
{
    if(!arg.value.has_value()) {
        error = "No format provided";
        return false;
    }


    if(*arg.value == "png"){
        rules.outputType = ImageType::PNG; 
    } else if(*arg.value == "jpg" || *arg.value == "jpeg"){
        rules.outputType = ImageType::JPEG; 
    } else if(*arg.value == "icns"){
        rules.outputType = ImageType::ICNS; 
    } else {
        error = "Unsupported output format.";
        return false;
    }

    return true;
}

bool RuleParserList::ParseResampleMode(const ArgParser::Argument &arg, Rules &rules, std::string &error)
{
    if(!arg.value.has_value()) {
        error = "No resampling mode provided";
        return false;
    }

    if(*arg.value == "nearest"){
        rules.ResampleMode = ResampleMode::Nearest; 
    } else if(*arg.value == "bilinear"){
        rules.ResampleMode = ResampleMode::Bilinear; 
    } else if(*arg.value == "trilinear"){
        rules.ResampleMode = ResampleMode::Trilinear; 
    } else {
        error = "Unsupported resample mode format: " + *arg.value;
        return false;
    }

    return true;
}

bool RuleParserList::ParseNewWidthHeight(const ArgParser::Argument &arg, Rules &rules, std::string &error)
{
    if(!arg.value.has_value()) {
        error = "No new dimensions provided.";
        return false;
    }
    
    std::string_view valueView = *arg.value;
    size_t colonPos = valueView.find_first_of(':');
    if (colonPos == std::string_view::npos || 
        colonPos == 0 || 
        colonPos == valueView.size() - 1 || 
        valueView.find_first_of(':', colonPos+1) != std::string_view::npos) 
    {
        error = "Incorrect new dimensions format. Use <Width>:<Height>. \nExample: 512:512";
        return false;
    }

    std::string_view left = valueView.substr(0, colonPos);
    std::string_view right = valueView.substr(colonPos + 1);

    uint64_t width, height;
    auto [ptrW, ecW] = std::from_chars(left.data(), left.data() + left.size(), width);
    auto [ptrH, ecH] = std::from_chars(right.data(), right.data() + right.size(), height);
    if (ecW != std::errc() || ptrW != left.data() + left.size() ||
        ecH != std::errc() || ptrH != right.data() + right.size()) 
    {
        error = "Couldn't read new dimensions. Only integer numbers are supported";
        return false;
    }

    auto operation = std::make_unique<NewWidthHighProcessingOperation>();

    operation->ResampleMode = rules.ResampleMode;
    operation->outputWidth = width;
    operation->outputHeight = height;

    rules.processingOperations.emplace_back(std::move(operation));
    return true;
}
