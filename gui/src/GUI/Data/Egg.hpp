/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Egg
*/

#pragma once

#include "Pos.hpp"

namespace GUI {
class Egg {
  public:
    Egg(int x, int y, int id) : id(id), pos({x, y}) {}

    Egg(Pos<int, 2> pos, int id) : id(id), pos(pos) {}

    int id;
    Pos<int, 2> pos;
};
} // namespace GUI
