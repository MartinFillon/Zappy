/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ArgParserException
*/

#pragma once

#include <exception>
#include <string>

class ArgParserException : public std::exception {
  public:
    ArgParserException(const std::string &what, const std::string &where = "?")
        : what_(what), where_(where)
    {
    }

    const char *what() const noexcept override
    {
        return what_.c_str();
    }

    const char *where() const noexcept
    {
        return where_.c_str();
    }

  private:
    std::string what_;
    std::string where_;
};
