/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Button
*/

#pragma once

#include "../Raylib.hpp"
#include "../Data/Pos.hpp"
#include <functional>

namespace GUI {

enum OpenWindow {
  MENU,
  SETTINGS,
  GAME,
  QUIT
};

class Button {
  public:
    Button(const std::string &name, std::function<void(OpenWindow&)> funct);

    void checkButtonAction(Rectangle &rec, OpenWindow &openWindow);
    void draw(Rectangle &rec, int fontSize);

  private:
    enum ButtonState {
      DEFAULT,
      HOVER,
      PRESSED
    };

    std::string m_name;
    std::function<void(OpenWindow&)> m_funct;
    ButtonState m_state;
};

} // namespace GUI
