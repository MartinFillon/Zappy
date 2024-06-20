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
    m_button.push_back(Button<Rectangle, OpenWindow>("start", [](OpenWindow &openWindow){openWindow = GAME;}));
    m_button.push_back(Button<Rectangle, OpenWindow>("settings", [](OpenWindow &openWindow){openWindow = SETTINGS;}));
    m_button.push_back(Button<Rectangle, OpenWindow>("quit", [](OpenWindow &openWindow){openWindow = QUIT;}));
}

void Menu::display()
{
    int fontSize = m_height / 8.0f;
    Rectangle rec = {m_width * 0.4f, m_height / 4.0f, m_width * 0.2f, fontSize + 20.0f};
    std::string name = "ZAPPY";
    int sizeText = Raylib::getMeasureTextEx(name, fontSize).x;

    Raylib::drawText(name, (m_width - sizeText) / 2, m_height / 8.0f, fontSize, PURPLE);
    for (size_t i = 0; i < m_button.size(); i++) {
        if (m_inPauseMenu && i == 0)
            continue;
        Button<Rectangle, OpenWindow> &but = m_button.at(i);
        rec.y += m_height / 8.0f;
        but.checkButtonAction(rec, m_openWindow);
        but.draw(rec, fontSize / 2.0f);
    }
}

} // namespace GUI
