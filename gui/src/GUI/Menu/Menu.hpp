/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Menu
*/

#pragma once

#include "Button.hpp"
#include "../../Network/Handler.hpp"
#include "window.hpp"
#include "AMenu.hpp"

namespace GUI {

class Menu : public AMenu {
  public:
    Menu(Network::Handler &networkHandler, Raylib::RecWin &newWindow);
    void display();

    void setClose(bool val);
    void setInGame(bool val);
    void setInSettings(bool val);
    bool getClose() const;
    bool getInGame() const;
    bool getInSettings() const;

  private:
    Network::Handler &networkHandler;

    std::vector<Button<Rectangle, bool>> m_button;
    Raylib::RecWin &m_newWindow;
    bool m_close;
    bool m_inGame;
    bool m_inSettings;
    };

} // namespace GUI
