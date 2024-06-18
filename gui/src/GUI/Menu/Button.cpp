/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Button
*/

#include "Button.hpp"

namespace GUI {

Button::Button(const std::string &name):
    m_name(name), m_funct([](void){}), m_state(DEFAULT)
{}

void Button::checkButtonAction(Rectangle &rec)
{
    if (Raylib::checkCollisionMouseRec(rec)) {
        if (Raylib::isMouseButtonDown(MOUSE_BUTTON_LEFT))
            m_state = PRESSED;
        else
            m_state = HOVER;
        if (Raylib::isMouseButtonReleased(MOUSE_BUTTON_LEFT))
            m_funct();
    } else {
        m_state = DEFAULT;
    }
}

void Button::draw(Rectangle &rec, int fontSize)
{
    Color colorRec = WHITE;
    Color colorText = BLACK;

    switch (m_state)
    {
    case HOVER:
        colorRec = GRAY;
        colorText = WHITE;
        break;
    case PRESSED:
        colorRec = GREEN;
        colorText = WHITE;
        break;
    default:
        break;
    }
    Raylib::drawRectangle(rec.x, rec.y, rec.width, rec.height, colorRec);
    Raylib::drawText(m_name, rec.x + rec.width / 2 - (m_name.size() * fontSize / 4), rec.y + (rec.height - fontSize * 1.5), fontSize, colorText);
}

} // namespace GUI
