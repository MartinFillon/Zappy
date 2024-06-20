/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Button
*/

#pragma once

#include <functional>

namespace GUI {

enum OpenWindow {
  MENU,
  SETTINGS,
  GAME,
  QUIT
};

template <typename F, typename T>
class IButton {
  public:
    virtual void checkButtonAction(F &rec, T &val) = 0;
    virtual void draw(F &rec, int fontSize) = 0;
};

} // namespace GUI
