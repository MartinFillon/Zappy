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
    virtual void toDefault(void) = 0;
    virtual void checkAction(F &f) = 0;
    virtual bool checkRecAction(F &f) = 0;
    virtual void draw(F &f, int fontSize) = 0;
};

} // namespace GUI
