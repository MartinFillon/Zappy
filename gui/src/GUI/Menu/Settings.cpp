/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Settings
*/

#include "Settings.hpp"


namespace GUI {

Settings::Settings(Raylib::RecWin &newWindow, MusicGame &music, bool &debug, bool is3D, bool isCameraFree, bool showCursor):
    AMenu(), m_newWindow(newWindow), m_is3D(is3D), m_isCameraFree(isCameraFree), m_showCursor(showCursor), m_debug(debug)
{
    m_button.push_back(CheckBox("3D", m_is3D, music));
    m_button.push_back(CheckBox("CameraFree", m_isCameraFree, music));
    m_button.push_back(CheckBox("ShowCursor", m_showCursor, music));
    m_button.push_back(CheckBox("Debug", m_debug, music));
    m_slider.push_back(Slider("Volume Music", music.getVolumeMusic(), music));
    m_slider.push_back(Slider("Volume Fx", music.getVolumeFx(), music));
    nb_but = m_button.size() + m_slider.size();
    m_iselected_but = nb_but - 1;
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
        if (!modeKey && but.checkRecAction(rec))
            m_iselected_but = i;
        if (modeKey) {
            if (m_iselected_but == i)
                but.checkAction(rec);
            else
                but.toDefault();
        }
        but.draw(rec, fontSize / 4.0f);
        rec.y += rec.size + SpacingSetButY;
    }
    rec.y += SpacingSetButY;
    Raylib::Line line = {static_cast<int>(rec.x),
        static_cast<int>(rec.y),
        static_cast<int>(rec.x + rec.size * 8),
        static_cast<int>(rec.y)};
    for (size_t i = 0; i < m_slider.size(); i++) {
        Slider &but = m_slider.at(i);
        if (!modeKey && but.checkRecAction(line))
            m_iselected_but = m_button.size() + i;
        if (modeKey) {
            if (m_iselected_but == m_button.size() + i)
                but.checkAction(line);
            else
                but.toDefault();
        }
        but.draw(line, fontSize / 4.0f);
        line.sy += SpacingSliderY + SpacingSetButY;
        line.ey = line.sy;
    }
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

} // namespace GUI
