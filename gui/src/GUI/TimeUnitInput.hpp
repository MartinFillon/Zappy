/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** TimeUnitInput
*/

#pragma once

#include <raylib.h>
#include <string>

#include "../Network/Handler.hpp"

class TimeUnitInput {
  public:
    TimeUnitInput(int initialValue, Network::Handler &networkHandler);
    void display(int x, int y, int width, int height) const;
    void handleEvent();
    int getTimeUnit() const;
    void setTimeUnit(int time);

  private:
    int timeUnit;
    int oldTimeUnit;
    std::string timeUnitStr;
    bool selected;
    size_t cursorPos;
    mutable float cursorBlinkTime;
    mutable bool cursorVisible;
    mutable int x, y, width, height;
    Network::Handler &networkHandler;
};
