/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Egg
*/

#pragma once

#include "Player.hpp"
#include "Pos.hpp"

namespace GUI {
class Egg {
  public:
    Egg(int x, int y, int id) : id(id), pos(x, y) {}

    Egg(Pos pos, int id) : id(id), pos(pos) {}

    int id;
    Pos pos;
}
} // namespace GUI
