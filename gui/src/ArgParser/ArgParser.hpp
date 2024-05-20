/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ArgParser
*/

#pragma once

#include <map>
#include <set>
#include <sstream>
#include <string>
#include <typeinfo>

#include "ArgParserException.hpp"

class ArgParser {
  public:
    ArgParser() = default;
    ~ArgParser() = default;

    void parse(int argc, char *argv[]);
    bool has(const std::string &param) const;

    template <typename T>
    ArgParser &setDefault(
        const std::string &param,
        T value,
        bool mandatory = false
    )
    {
        std::stringstream ss;
        ss << value;
        params_[param] = ss.str();
        types_[param] = typeid(T).name();
        if (mandatory) {
            mandatoryArgs_.insert(param);
        }
        return *this;
    }

    template <typename T>
    T get(const std::string &param) const
    {
        if (params_.find(param) == params_.end()) {
            throw ArgParserException(
                "Parameter not found: " + param, "ArgParser::get"
            );
        } else if (types_.at(param) != typeid(T).name()) {
            throw ArgParserException(
                "Type mismatch for parameter: " + param, "ArgParser::get"
            );
        }
        std::istringstream ss(params_.at(param));
        T value;

        ss >> value;
        return value;
    }

  private:
    std::map<std::string, std::string> params_;
    std::map<std::string, std::string> types_;
    std::set<std::string> mandatoryArgs_;

    void checkMandatoryArgs(const std::set<std::string> &providedArgs) const;
    bool isValidType(const std::string &key, const std::string &value) const;
};
