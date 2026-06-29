#pragma once

#include "Rules.h"

#include <string>

class RulesValidator {
    bool ValidateICNS(const Rules& rules, std::string& error);
public:
    bool Validate(const Rules& rules, std::string& error);
};