/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** TimeUnitInput
*/

#pragma once

#include "Raylib.hpp"
#include <string>

#include "../Network/Handler.hpp"

class TimeUnitInput {
  public:
    TimeUnitInput(int initialValue, Network::Handler &networkHandler);
    void display() const;
    void handleEvent();
    int getTimeUnit() const;
    void setTimeUnit(int time);
    void resize(int x, int y, int width, int height);

  private:
    int timeUnit;
    int oldTimeUnit;
    std::string timeUnitStr;
    bool selected;
    size_t cursorPos;
    mutable float cursorBlinkTime;
    mutable bool cursorVisible;
    int x, y, width, height;
    Network::Handler &networkHandler;
};
