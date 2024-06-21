/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Button
*/

#pragma once

#include "AButton.hpp"
#include <functional>

namespace GUI {

template <typename F, typename T>
class Button : public AButton<F, T>
{
  public:
    Button(const std::string &name, T &val, std::function<void(T&)> funct):
      AButton<F, T>(name, val, funct) {}

    void checkButtonAction(F &rec) override {
        if (Raylib::checkCollisionMouseRec(rec)) {
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

    void draw(F &forme, int fontSize) override {
        Color colorRec = WHITE;
        Color colorText = BLACK;

        switch (this->m_state)
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
        Raylib::draw(forme, colorRec);
        Raylib::drawTextInForm(this->m_name, forme, fontSize, colorText);
    }
};

} // namespace GUI
