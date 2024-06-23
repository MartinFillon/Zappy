/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Settings
*/

#pragma once

#include "CheckBox.hpp"
#include "Slider.hpp"
#include "window.hpp"
#include "AMenu.hpp"

namespace GUI {

class Settings : public AMenu {
  public:
    Settings(Raylib::RecWin &m_newWindow, MusicGame &music, bool &debug, bool is3D = true, bool isCameraFree = false, bool showCursor = true);
    void display();

    bool is3D();
    bool isCameraFree();
    bool showCursor();
    void switchIs3D();
    void switchIsCameraFree();
    void switchShowCursor();

  private:
    std::vector<CheckBox> m_button;
    std::vector<Slider> m_slider;
    Raylib::RecWin &m_newWindow;

    bool m_is3D;
    bool m_isCameraFree;
    bool m_showCursor;
    bool &m_debug;
   };

} // namespace GUI
