#pragma once

#include <vector>
#include <string>
#include <optional>
#include <string_view>
#include <unordered_map>

class ArgParser {
    struct Argument {
        std::string key;
        std::optional<std::string_view> value;
    };

    std::vector<Argument> m_arguments;
    std::vector<std::string> m_inputs;
public:
    ArgParser(int argc, char ** argv) {
        bool bExpectValue = false;
        std::string_view pendingKey;
        for(int i = 1; i < argc; i++) {
            std::string_view arg = argv[i];

            if(!bExpectValue) {
                if(arg.starts_with("--")) {
                    arg.remove_prefix(2);
                    pendingKey = arg;
                    bExpectValue = true;
                } else if(arg.starts_with("-")) {
                    arg.remove_prefix(1);
                    m_arguments.emplace_back({arg, std::nullopt});  
                } else {
                    m_inputs.emplace_back(arg);
                }
            } else {
                m_arguments.emplace_back({pendingKey, arg});
                bExpectValue = false;
            }
        }
    }

    size_t GetCount() const {return m_arguments.size();}

    bool Has(std::string_view argument) const {
        for(const Argument& arg : m_arguments) {
            if(arg.key == argument) {
                return true;
            }
        }

        return false;
    }

    std::optional<std::string_view> Get(std::string_view argument) const {
        for(const Argument& arg : m_arguments) {
            if(arg.key == argument) {
                return arg.value;
            }
        }

        return std::nullopt;
    }

    const std::vector<std::string>& GetInputs() const {return m_inputs;}
};