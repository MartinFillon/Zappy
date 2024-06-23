/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Settings
*/

#include "Settings.hpp"


namespace GUI {

Settings::Settings(Raylib::RecWin &newWindow, bool &debug, bool is3D, bool isCameraFree, bool showCursor):
    m_newWindow(newWindow), m_is3D(is3D), m_isCameraFree(isCameraFree), m_showCursor(showCursor), m_debug(debug)
{
    m_button.push_back(CheckBox("3D", m_is3D));
    m_button.push_back(CheckBox("CameraFree", m_isCameraFree));
    m_button.push_back(CheckBox("ShowCursor", m_showCursor));
    m_button.push_back(CheckBox("Debug", m_debug));
}

bool Settings::is3D() const
{
    return m_is3D;
}

bool Settings::isCameraFree() const
{
    return m_isCameraFree;
}

bool Settings::showCursor() const
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
    float fontSize = HeightToFontSize(m_newWindow.height);
    Raylib::Square rec = {
        m_newWindow.x + m_newWindow.width * MulSetPosButton,
        m_newWindow.y + m_newWindow.height * MulStrtY,
        m_newWindow.height * MulSizeCheckBox};
    std::string name = "SETTINGS";
    int sizeText = Raylib::getMeasureTextEx(name, fontSize).x;

    Raylib::drawText(name,
        m_newWindow.x + (m_newWindow.width - sizeText) / 2.0f,
        m_newWindow.y + m_newWindow.height * MulNameY,
        fontSize, PURPLE);
    for (size_t i = 0; i < m_button.size(); i++) {
        CheckBox &but = m_button.at(i);
        but.checkButtonAction(rec);
        but.draw(rec, fontSize / 4.0f);
        rec.y += rec.size + SpacingSetButY;
    }
}

} // namespace GUI
