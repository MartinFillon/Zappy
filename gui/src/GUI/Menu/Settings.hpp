/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Settings
*/

#pragma once

#include "CheckBox.hpp"
#include "window.hpp"

namespace GUI {

class Settings {
  public:
    Settings(Raylib::RecWin &m_newWindow, bool is3D = true, bool isCameraFree = false, bool showCursor = true);
    bool is3D();
    bool isCameraFree();
    bool showCursor();
    void switchIs3D();
    void switchIsCameraFree();
    void switchShowCursor();
    void display();

  private:
    std::vector<CheckBox> m_button;
    Raylib::RecWin &m_newWindow;

    bool m_is3D;
    bool m_isCameraFree;
    bool m_showCursor;
   };

} // namespace GUI
