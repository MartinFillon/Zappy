/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Button
*/

#pragma once

#include "../Raylib.hpp"
#include <functional>

namespace GUI {

template <typename F, typename T>
class IButton {
  public:
    virtual void checkButtonAction(F &rec) = 0;
    virtual void draw(F &rec, int fontSize) = 0;
};

} // namespace GUI
