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

/**
 * @class ArgParser
 * @brief A class to parse and handle command-line arguments.
 *
 * This class provides methods to parse command-line arguments, set default
 * values for parameters, check for the presence of parameters, and retrieve
 * parameter values with type safety.
 */
class ArgParser {
  public:
    ArgParser() = default;
    ~ArgParser() = default;

    /**
     * @brief Parses command-line arguments.
     *
     * @param argc The number of command-line arguments.
     * @param argv The array of command-line arguments.
     */
    void parse(int argc, char *argv[]);

    /**
     * @brief Checks if a parameter is present.
     *
     * @param param The name of the parameter to check.
     * @return true if the parameter is present, false otherwise.
     */
    bool has(const std::string &param) const;

    /**
     * @brief Sets a default value for a parameter.
     *
     * @tparam T The type of the parameter value.
     * @param param The name of the parameter.
     * @param value The default value of the parameter.
     * @param mandatory Whether the parameter is mandatory (default is false).
     * @return A reference to the ArgParser object.
     */
    template <typename T>
    ArgParser &setDefault(const std::string &param, T value, bool mandatory = false)
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

    /**
     * @brief Retrieves the value of a parameter.
     *
     * @tparam T The type of the parameter value.
     * @param param The name of the parameter.
     * @return The value of the parameter.
     * @throws ArgParserException if the parameter is not found or if there is a
     * type mismatch.
     */
    template <typename T>
    T get(const std::string &param) const
    {
        if (params_.find(param) == params_.end()) {
            throw ArgParserException("Parameter not found: " + param, "ArgParser::get");
        } else if (types_.at(param) != typeid(T).name()) {
            throw ArgParserException("Type mismatch for parameter: " + param, "ArgParser::get");
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
    /**
     * @brief Checks if all mandatory arguments are provided.
     *
     * @param providedArgs The set of provided argument names.
     * @throws ArgParserException if a mandatory argument is missing.
     */
    void checkMandatoryArgs(const std::set<std::string> &providedArgs) const;

    /**
     * @brief Validates the type of a parameter value.
     *
     * @param key The name of the parameter.
     * @param value The value of the parameter as a string.
     * @return true if the type is valid, false otherwise.
     */
    bool isValidType(const std::string &key, const std::string &value) const;
};
