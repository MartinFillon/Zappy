/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** AMenu
*/

#pragma once

#include "IMenu.hpp"

namespace GUI {

class AMenu : public IMenu {
  public:
    AMenu() : nb_but(0), m_iselected_but(0), modeKey(false) {};

    void eventhandler() override {
      Vector2 cursorMove = GetMouseDelta();
      if (modeKey && (cursorMove.x > 0.001f || cursorMove.y > 0.001f )) {
          modeKey = false;
      }
      if (Raylib::isKeyPressed(KEY_UP)) {
          m_iselected_but = (m_iselected_but == 0) ? nb_but - 1 : m_iselected_but - 1;
          modeKey = true;
      }
      if (Raylib::isKeyPressed(KEY_DOWN)) {
          m_iselected_but = ((m_iselected_but + 1) % nb_but);
          modeKey = true;
      }
    };

  protected:
    size_t nb_but;
    size_t m_iselected_but;
    bool modeKey;
};

} // namespace GUI
