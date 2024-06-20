/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** CheckBox
*/

#pragma once

#include "AButton.hpp"
#include <functional>

namespace GUI {

class CheckBox : public AButton<Raylib::Square, bool>
{
  public:
    CheckBox(const std::string &name, bool &val):
      AButton<Raylib::Square, bool>(name, val, [](bool &val){val = !val;}) {}

    void checkButtonAction(Raylib::Square &sqr) override {
        if (Raylib::checkCollisionMouseSquare(sqr)) {
            if (Raylib::isMouseButtonDown(MOUSE_BUTTON_LEFT))
                this->m_state = PRESSED;
            else
                this->m_state = HOVER;
            if (Raylib::isMouseButtonReleased(MOUSE_BUTTON_LEFT))
                this->m_funct(this->m_val);
        } else {
            this->m_state = DEFAULT;
        }
    }

    void draw(Raylib::Square &sqr, int fontSize) override {
        Color colorRec = BLUE;
        Color colorBackRec = WHITE;
        Color colorText = BLACK;
        Raylib::Square lightRec = {sqr.x + 5, sqr.y + 5, sqr.size - 10};

        switch (this->m_state)
        {
        case HOVER:
            colorRec = GRAY;
            break;
        case PRESSED:
            colorRec = GREEN;
            break;
        default:
            break;
        }
        Raylib::drawSquare(sqr, colorBackRec);
        Raylib::drawSquareLines(sqr, colorRec);
        if (m_val)
            Raylib::drawSquare(lightRec, colorRec);
        Raylib::drawText(this->m_name, sqr.x + sqr.size + 20, sqr.y, fontSize, colorText);
    }
};

} // namespace GUI
