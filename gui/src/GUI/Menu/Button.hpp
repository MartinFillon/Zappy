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

class Button {
  public:
    Button(const std::string &name);

    void checkButtonAction(Rectangle &rec);
    void draw(Rectangle &rec, int fontSize);

  private:
    enum ButtonState {
      DEFAULT,
      HOVER,
      PRESSED
    };

    std::string m_name;
    std::function<void()> m_funct;
    ButtonState m_state;
};

} // namespace GUI
