/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Egg
*/

#pragma once

#include "Pos.hpp"

namespace GUI {
namespace Data {

class Egg {
  public:
    Egg(int x, int y, int id) : id(id), pos({x, y}), hatched(false) {}

    Egg(Pos<int, 2> pos, int id) : id(id), pos(pos), hatched(false) {}

    int getId() const
    {
        return id;
    }

    Pos<int, 2> getPosition() const
    {
        return pos;
    }

    bool isHatched() const
    {
        return hatched;
    }

    void hatch()
    {
        hatched = true;
    }

  private:
    int id;
    Pos<int, 2> pos;
    bool hatched;
};

} // namespace Data
} // namespace GUI
