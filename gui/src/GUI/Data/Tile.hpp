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

    void updateRessources(int q0, int q1, int q2, int q3, int q4, int q5, int q6)
    {
        m_inv.update(q0, q1, q2, q3, q4, q5, q6);
    }

  private:
    Inventory m_inv;
};
} // namespace Data
} // namespace GUI
