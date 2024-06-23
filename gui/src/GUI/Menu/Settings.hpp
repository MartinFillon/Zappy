/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Settings
*/

#pragma once

#include "CheckBox.hpp"
#include "AMenu.hpp"

namespace GUI {

class Settings : public AMenu {
  public:
    Settings(Raylib::RecWin &m_newWindow, bool &debug, bool is3D = true, bool isCameraFree = false, bool showCursor = true);
    void display();
    bool is3D() const;
    bool isCameraFree() const;
    bool showCursor() const;
    void switchIs3D();
    void switchIsCameraFree();
    void switchShowCursor();

  private:
    std::vector<CheckBox> m_button;
    Raylib::RecWin &m_newWindow;

    bool m_is3D;
    bool m_isCameraFree;
    bool m_showCursor;
    bool &m_debug;
   };

} // namespace GUI
