/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Tile
*/

#pragma once

#include "Inventory.hpp"

namespace GUI {
namespace Data {
class Tile {
  public:
    Tile() = default;
    ~Tile() = default;

    Inventory &getRessources()
    {
        return m_inv;
    };

  private:
    Inventory m_inv;
};
} // namespace Data
} // namespace GUI
