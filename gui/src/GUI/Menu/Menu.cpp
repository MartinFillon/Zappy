/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Menu
*/

#include "Menu.hpp"


namespace GUI {

Menu::Menu(Network::Handler &networkHandler, int &screenWidth, int &screenHeight):
    networkHandler(networkHandler), m_width(screenWidth), m_height(screenHeight), m_close(false), m_inGame(false), m_inSettings(false)
{
    m_button.push_back(Button<Rectangle, bool>("start", m_inGame, [](bool &val){val = true;}));
    m_button.push_back(Button<Rectangle, bool>("settings", m_inSettings, [](bool &val){val = true;}));
    m_button.push_back(Button<Rectangle, bool>("quit", m_close, [](bool &val){val = true;}));
}

void Menu::display()
{
    int fontSize = m_height / 8.0f;
    Rectangle rec = {m_width * 0.4f, m_height / 4.0f, m_width * 0.2f, fontSize + 20.0f};
    std::string name = "ZAPPY";
    int sizeText = Raylib::getMeasureTextEx(name, fontSize).x;
    bool inGame = m_inGame;

    Raylib::drawText(name, (m_width - sizeText) / 2, m_height / 8.0f, fontSize, PURPLE);
    for (size_t i = 0; i < m_button.size(); i++) {
        Button<Rectangle, bool> &but = m_button.at(i);
        rec.y += rec.height;
        but.checkButtonAction(rec);
        but.draw(rec, fontSize / 2.0f);
    }
    if (inGame != m_inGame) {
        networkHandler.start();
    }
}

void Menu::setClose(bool val)
{
    m_close = val;
}

void Menu::setInGame(bool val)
{
    m_inGame = val;
}

void Menu::setInSettings(bool val)
{
    m_inSettings = val;
}

bool Menu::getClose() const
{
    return m_close;
}

bool Menu::getInGame() const
{
    return m_inGame;
}

bool Menu::getInSettings() const
{
    return m_inSettings;
}

} // namespace GUI
