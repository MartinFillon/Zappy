/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ArgParserException
*/

#pragma once

#include <exception>
#include <string>

/**
 * @class ArgParserException
 * @brief Exception class for argument parser errors.
 */
class ArgParserException : public std::exception {
  public:
    /**
     * @brief Constructs an ArgParserException.
     *
     * @param what A description of the error.
     * @param where The location where the exception was thrown (default: "?").
     */
    ArgParserException(const std::string &what, const std::string &where = "?")
        : what_(what), where_(where)
    {
    }

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
