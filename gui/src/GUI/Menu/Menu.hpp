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

    void setClose(bool val);
    void setInGame(bool val);
    void setInSettings(bool val);
    bool getClose() const;
    bool getInGame() const;
    bool getInSettings() const;

  private:
    std::vector<Button<Rectangle, bool>> m_button;
    int &m_width;
    int &m_height;
    bool m_close;
    bool m_inGame;
    bool m_inSettings;
    };

} // namespace GUI
