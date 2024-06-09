/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** TimeUnitInput
*/

#pragma once

#include <raylib.h>
#include <string>

class TimeUnitInput {
  public:
    TimeUnitInput(int initialValue);
    void display(int x, int y, int width, int height) const;
    void handleEvent();
    int getTimeUnit() const;

  private:
    int timeUnit;
    int oldTimeUnit;
    std::string timeUnitStr;
    bool selected;
    size_t cursorPos;
    mutable float cursorBlinkTime;
    mutable bool cursorVisible;
    mutable int x, y, width, height;
};
