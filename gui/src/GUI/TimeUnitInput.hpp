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
#include "UIComponent.hpp"

class TimeUnitInput : public UIComponent {
  public:
    TimeUnitInput(int initialValue, Network::Handler &networkHandler);
    void display() const override;
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
    Network::Handler &networkHandler;
};
