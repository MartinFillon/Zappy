/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Menu
*/

#pragma once

#include "Button.hpp"

namespace GUI {

class Menu {
  public:
    Menu(int &screenWidth, int &screenHeight);
    void display();

  private:
    std::vector<Button> m_button;
    int &m_width;
    int &m_height;
    bool m_inPauseMenu;
};

} // namespace GUI
