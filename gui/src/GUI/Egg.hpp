/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Egg
*/

#pragma once

#include <cstddef>
#include "Pos.hpp"

namespace GUI {
class Egg {
  public:
    Egg(int x, int y, int id) : id(id), pos(x, y) {}
    Egg(Pos<int> pos, int id) : id(id), pos(pos) {}

    int id;
    Pos<int> pos;
};
} // namespace GUI
