/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Menu
*/

#include "Menu.hpp"


namespace GUI {

Menu::Menu(int &screenWidth, int &screenHeight, OpenWindow &openWindow):
    m_width(screenWidth), m_height(screenHeight), m_inPauseMenu(false), m_openWindow(openWindow)
{
    m_button.push_back(Button("start", [](OpenWindow &openWindow){openWindow = GAME;}));
    m_button.push_back(Button("settings", [](OpenWindow &openWindow){openWindow = SETTINGS;}));
    m_button.push_back(Button("quit", [](OpenWindow &openWindow){openWindow = QUIT;}));
}

void Menu::display()
{
    int fontSize = m_height / 8.0f;
    Rectangle rec = {m_width * 0.4f, m_height / 4.0f, m_width * 0.2f, fontSize + 20.0f};

    Raylib::drawText("ZAPPY", m_width / 2.0f - fontSize * 1.5f, m_height / 8.0f, fontSize, PURPLE);
    for (size_t i = 0; i < m_button.size(); i++) {
        if (m_inPauseMenu && i == 0)
            continue;
        Button &but = m_button.at(i);
        rec.y += m_height / 8.0f;
        but.checkButtonAction(rec, m_openWindow);
        but.draw(rec, fontSize / 2.0f);
    }
}

} // namespace GUI
