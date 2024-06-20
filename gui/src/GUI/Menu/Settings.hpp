/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Settings
*/

#pragma once

#include "CheckBox.hpp"

namespace GUI {

class Settings {
  public:
    Settings(int &screenWidth, int &screenHeight, bool is3D = true, bool isCameraFree = false, bool showCursor = true);
    bool is3D();
    bool isCameraFree();
    bool showCursor();
    void switchIs3D();
    void switchIsCameraFree();
    void switchShowCursor();
    void display();

  private:
    std::vector<CheckBox> m_button;
    int &m_width;
    int &m_height;

    bool m_is3D;
    bool m_isCameraFree;
    bool m_showCursor;
   };

} // namespace GUI
