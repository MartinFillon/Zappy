/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** TimeUnitInput
*/

#include "TimeUnitInput.hpp"

TimeUnitInput::TimeUnitInput(int initialValue, Network::Handler &networkHandler)
    : timeUnit(initialValue), oldTimeUnit(initialValue), timeUnitStr(std::to_string(initialValue)), selected(false),
      cursorPos(timeUnitStr.length()), cursorBlinkTime(0.0f), cursorVisible(true), networkHandler(networkHandler)
{
}

void TimeUnitInput::display() const
{
    Color boxColor = selected ? DARKGRAY : LIGHTGRAY;
    Raylib::drawText("Tick Duration:", x, y - 30, 20, LIGHTGRAY);
    Raylib::drawRectangle(x, y, width, height, boxColor);
    Raylib::drawText(timeUnitStr, x + 5, y + 5, 20, BLACK);

    if (selected && cursorVisible) {
        int textWidth = MeasureText(timeUnitStr.substr(0, cursorPos).c_str(), 20);
        Raylib::drawLine(x + 5 + textWidth, y + 5, x + 5 + textWidth, y + height - 5, BLACK);
    }
}

void TimeUnitInput::handleEvent()
{
    cursorBlinkTime += Raylib::getFrameTime();
    if (cursorBlinkTime >= 0.5f) {
        cursorVisible = !cursorVisible;
        cursorBlinkTime = 0.0f;
    }

    if (Raylib::checkCollisionMouseRec(
            static_cast<float>(x), static_cast<float>(y), static_cast<float>(width), static_cast<float>(height)
        )) {
        if (Raylib::isMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            selected = true;
            oldTimeUnit = timeUnit;
            cursorPos = timeUnitStr.length();
        }
    } else if (Raylib::isMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (selected) {
            timeUnit = oldTimeUnit;
            timeUnitStr = std::to_string(timeUnit);
        }
        selected = false;
    }

    if (selected) {
        int key = Raylib::getKeyPressed();
        if (key >= 48 && key <= 57) {
            if (timeUnitStr.length() < 10) {
                timeUnitStr.insert(cursorPos, 1, static_cast<char>(key));
                cursorPos++;
            }
        }
        if (key == KEY_BACKSPACE && cursorPos > 0) {
            timeUnitStr.erase(cursorPos - 1, 1);
            cursorPos--;
        }
        if (key == KEY_DELETE && cursorPos < timeUnitStr.length()) {
            timeUnitStr.erase(cursorPos, 1);
        }
        if (key == KEY_ENTER && !timeUnitStr.empty()) {
            timeUnit = std::stoi(timeUnitStr);
            timeUnitStr = std::to_string(timeUnit);
            selected = false;
            networkHandler.modifyTimeUnit(timeUnit);
        }
        if (key == KEY_ESCAPE) {
            timeUnit = oldTimeUnit;
            timeUnitStr = std::to_string(timeUnit);
            selected = false;
        }
        if (key == KEY_LEFT && cursorPos > 0) {
            cursorPos--;
        }
        if (key == KEY_RIGHT && cursorPos < timeUnitStr.length()) {
            cursorPos++;
        }
    }
}

int TimeUnitInput::getTimeUnit() const
{
    return timeUnit;
}

void TimeUnitInput::setTimeUnit(int time)
{
    timeUnit = time;
    if (!selected) {
        timeUnitStr = std::to_string(timeUnit);
    }
}
