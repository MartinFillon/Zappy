/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Error
*/

#pragma once

#include <exception>
#include <string>

namespace ArgParser {
/**
 * @class Error
 * @brief Error class for argument parser errors.
 */
class Error : public std::exception {
  public:
    /**
     * @brief Constructs an Error.
     *
     * @param what A description of the error.
     * @param where The location where the exception was thrown (default: "?").
     */
    Error(const std::string &what, const std::string &where = "?") : what_(what), where_(where) {}

    /**
     * @brief Returns the description of the error.
     *
     * @return A C-string containing the error description.
     */
    const char *what() const noexcept override
    {
        return what_.c_str();
    }

    /**
     * @brief Returns the location where the exception was thrown.
     *
     * @return A C-string containing the location description.
     */
    const char *where() const noexcept
    {
        return where_.c_str();
    }

  private:
    std::string what_;
    std::string where_;
};
}; // namespace ArgParser
