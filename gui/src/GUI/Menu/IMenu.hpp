/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** IMenu
*/

#pragma once

#include "../Raylib.hpp"

namespace GUI {

class IMenu {
  public:
    virtual void display() = 0;
    virtual void eventhandler() = 0;
};

} // namespace GUI
