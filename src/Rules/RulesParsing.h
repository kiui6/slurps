#pragma once

#include <unordered_map>

#include "Rules.h"
#include <ArgParser.h>

class RuleParserList {
    static bool ParseOutput(const ArgParser::Argument& arg, Rules& rules, std::string& error);
    static bool ParseFormat(const ArgParser::Argument& arg, Rules& rules, std::string& error);
    static bool ParseResampleMode(const ArgParser::Argument& arg, Rules& rules, std::string& error);
    static bool ParseNewWidthHeight(const ArgParser::Argument& arg, Rules& rules, std::string& error);

    static const std::unordered_map<std::string, bool (*)(const ArgParser::Argument&, Rules&, std::string&)> m_list;
public:
    static bool TryParse(const ArgParser::Argument& arg, Rules& rules, std::string& error) {
        auto it = m_list.find(arg.key);
        if(it != m_list.end()) {
            return it->second(arg, rules, error);
        } else {
            return true;
        }
    }
};

static inline bool ParseRules(const ArgParser& args, Rules& rules, std::string& error) {
    if(args.GetInputs().size() == 0) {
        error = "No input files.";
        return false;
    }

    rules.inputs = std::move(args.GetInputs());
    
    // Processing stages
    for(const auto& argument : args.GetArguments()) {
        if(!RuleParserList::TryParse(argument, rules, error)) {
            return false;
        }
    }

    if(rules.output.empty()) {
        error = "No output template provided";
    }
    
    return true;
}