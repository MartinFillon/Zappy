/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Map
*/

#pragma once

#include <vector>

#include "Egg.hpp"
#include "Player.hpp"
#include "Pos.hpp"
#include "Tile.hpp"

namespace GUI {
namespace Data {
class Map {
  public:
    Map(int x, int y) : m_size(Pos<int, 2>({x, y})){};
    Map(Pos<int, 2> &pos) : m_size(pos){};
    ~Map() = default;

    Tile &getTile(Pos<int, 2> &pos)
    {
        return m_map.at(pos.y() * m_size.x() + pos.x());
    };

    Tile &getTile(int x, int y)
    {
        return m_map.at(y * x + x);
    };

    std::vector<Player> &getPlayers()
    {
        return m_players;
    };

    std::vector<Egg> getEggs() const
    {
        return m_egg;
    };

    Pos<int, 2> getSize() const
    {
        return m_size;
    };

    void resize(int x, int y)
    {
        int new_size = m_size.x() * m_size.y();

        if (x * y < new_size)
            m_map.resize(new_size);
        m_size = {x, y};
    }

    void resize (Pos<int, 2> size)
    {
        int new_size = m_size.x() * m_size.y();

        if (size.x() * size.y() < new_size)
            m_map.resize(new_size);
        m_size = size;
    }

  private:
    std::vector<Tile> m_map;
    std::vector<Player> m_players;
    std::vector<Egg> m_egg;
    Pos<int, 2> m_size;
};
} // namespace Data
} // namespace GUI
