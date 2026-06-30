#include "RulesParsing.h"

const std::unordered_map<std::string, bool (*)(const ArgParser::Argument&, Rules&, std::string&)> RuleParserList::m_list = {
    {"output", RuleParserList::ParseOutput},
    {"format", RuleParserList::ParseFormat},
    {"resampleMode", RuleParserList::ParseResampleMode},
    {"newWidthHeight", RuleParserList::ParseNewWidthHeight},
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
    auto operation = std::make_unique<NewWidthHighProcessingOperation>();

    operation->ResampleMode = rules.ResampleMode;

    rules.processingOperations.emplace_back(std::move(operation));
    return true;
}
