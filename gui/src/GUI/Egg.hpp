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
    Egg(size_t x, size_t y, size_t id) : id(id), pos(x, y) {}
    Egg(Pos<size_t> pos, size_t id) : id(id), pos(pos) {}

    
    size_t id;
    Pos<size_t> pos;
};
} // namespace GUI
