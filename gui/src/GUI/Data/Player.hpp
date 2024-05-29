/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Player
*/

#pragma once

#include "Inventory.hpp"
#include "Pos.hpp"

namespace GUI {
namespace Data {
class Player {
  public:
    Player(int &x, int &y, int &id) : m_pos(Pos<int, 2>({x, y})), m_id(id){};
    Player(Pos<int, 2> &pos, int &id) : m_pos(pos), m_id(id){};
    ~Player() = default;

    Pos<int, 2> getPos()
    {
        return m_pos;
    };

    Inventory getRessources()
    {
        return m_inv;
    };

    int getLevel()
    {
        return m_level;
    };

    int getId()
    {
        return m_id;
    };

  private:
    Pos<int, 2> m_pos;
    Inventory m_inv;
    int m_level;
    int m_id;
};
} // namespace Data
} // namespace GUI
