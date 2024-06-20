/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Settings
*/

#include "Settings.hpp"


namespace GUI {

Settings::Settings(int &screenWidth, int &screenHeight, bool is3D, bool isCameraFree, bool showCursor):
    m_width(screenWidth), m_height(screenHeight), m_is3D(is3D), m_isCameraFree(isCameraFree), m_showCursor(showCursor)
{
    m_button.push_back(CheckBox("3D", m_is3D));
    m_button.push_back(CheckBox("CameraFree", m_isCameraFree));
    m_button.push_back(CheckBox("showCursor", m_showCursor));
}

bool Settings::is3D()
{
    return m_is3D;
}

bool Settings::isCameraFree()
{
    return m_isCameraFree;
}

bool Settings::showCursor()
{
    return m_showCursor;
}

void Settings::switchIs3D()
{
    m_is3D = !m_is3D;
}

void Settings::switchIsCameraFree()
{
    m_isCameraFree = !m_isCameraFree;
}

void Settings::switchShowCursor()
{
    m_showCursor = !m_showCursor;
}

void Settings::display()
{
    float fontSize = m_height / 8.0f;
    Raylib::Square rec = {m_width * 0.3f, m_height / 4.0f, fontSize};

    for (size_t i = 0; i < m_button.size(); i++) {
        CheckBox &but = m_button.at(i);
        rec.y += rec.size + 20.0f;
        but.checkButtonAction(rec);
        but.draw(rec, fontSize / 2.0f);
    }
}

} // namespace GUI
