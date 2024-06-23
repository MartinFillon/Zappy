/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Slider
*/

#pragma once

#include "AButton.hpp"
#include "window.hpp"
#include <functional>
#include <algorithm>

namespace GUI {

class Slider : public AButton<Raylib::Line, float>
{
  public:
    Slider(const std::string &name, float &val, MusicGame &music):
      AButton<Raylib::Line, float>(name, val, music) {}

    void toDefault(void) override {
        this->m_state = DEFAULT;
    }

    void checkAction(const Raylib::Line &line) override {
        if (Raylib::isMouseButtonDown(MOUSE_BUTTON_LEFT) || IsKeyDown(KEY_ENTER)) {
            updateValue(line);
            this->m_state = PRESSED;
        }
        else
            this->m_state = HOVER;
        if (Raylib::isMouseButtonReleased(MOUSE_BUTTON_LEFT) || IsKeyReleased(KEY_ENTER)) {
            updateValue(line);
            this->m_music.playSound();
        }
    }

    bool checkRecAction(const Raylib::Line &refLine) override {
        Raylib::Line line = {refLine.sx, refLine.sy + SpacingSliderY, refLine.ex, refLine.ey + SpacingSliderY};
        Raylib::Circle cir = getCirle(line);

        if (this->m_state == PRESSED && (Raylib::isMouseButtonDown(MOUSE_BUTTON_LEFT) || IsKeyDown(KEY_ENTER))) {
            updateValue(line);
            return true;
        }
        if (Raylib::checkCollisionMouseCircle(cir)) {
            checkAction(line);
            return true;
        }
        this->m_state = DEFAULT;
        return false;
    }

    void draw(const Raylib::Line &refLine, int fontSize) override {
        Color colorCircle = BLACK;
        int sy = refLine.sy;
        Raylib::Line line = {refLine.sx, refLine.sy + SpacingSliderY, refLine.ex, refLine.ey + SpacingSliderY};
        Raylib::Circle cir = getCirle(line);

        switch (this->m_state)
        {
        case HOVER:
            colorCircle = GRAY;
            break;
        case PRESSED:
            colorCircle = GREEN;
            break;
        default:
            break;
        }
        Raylib::drawLine(line, BLACK);
        Raylib::drawCircle(cir, colorCircle);
        Raylib::drawText(this->m_name, line.sx, sy, fontSize, BLACK);
    }

    Raylib::Circle getCirle(const Raylib::Line &line) {
        return (Raylib::Circle){
            static_cast<float>(line.sx + (line.ex - line.sx) * m_val),
            static_cast<float>(line.ey),
            static_cast<float>(std::max(line.ex - line.sx, line.ey - line.sy) / 20)};
    }

    void updateValue(const Raylib::Line &line) {
        float xMouse = Raylib::getMousePosition().x;
        if (xMouse < static_cast<float>(line.sx))
            xMouse = static_cast<float>(line.sx);
        if (xMouse > static_cast<float>(line.ex))
            xMouse = static_cast<float>(line.ex);
        m_val = (xMouse - line.sx) / (line.ex - line.sx);
    }
};

} // namespace GUI
