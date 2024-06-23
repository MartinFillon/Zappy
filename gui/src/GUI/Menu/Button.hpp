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
    Button(const std::string &name, T &val, std::function<void(T&)> funct, MusicGame &music):
      AButton<F, T>(name, val, funct, music) {}

    void toDefault(void) override {
        this->m_state = DEFAULT;
    }

    void checkAction(void) override {
        if (Raylib::isMouseButtonDown(MOUSE_BUTTON_LEFT) || IsKeyDown(KEY_ENTER))
            this->m_state = PRESSED;
        else
            this->m_state = HOVER;
        if (Raylib::isMouseButtonReleased(MOUSE_BUTTON_LEFT) || IsKeyReleased(KEY_ENTER)) {
            this->m_funct(this->m_val);
            this->m_music.playSound();
        }
    }

    bool checkRecAction(F &rec) override {
        if (Raylib::checkCollisionMouseRec(rec)) {
            checkAction();
            return true;
        }
        this->m_state = DEFAULT;
        return false;
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
