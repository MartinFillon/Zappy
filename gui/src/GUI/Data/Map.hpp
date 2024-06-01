/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Map
*/

#pragma once

#include <stdexcept>
#include <vector>
#include "Egg.hpp"
#include "Player.hpp"
#include "Pos.hpp"
#include "Tile.hpp"

namespace GUI {
namespace Data {

class Map {
  public:
    Map(int x, int y) : m_size({x, y})
    {
        m_map.resize(x * y);
    }

    Map(const Pos<int, 2> &pos) : m_size(pos)
    {
        m_map.resize(pos.x() * pos.y());
    }

    Tile &getTile(const Pos<int, 2> &pos)
    {
        if (pos.x() >= m_size.x() || pos.y() >= m_size.y()) {
            throw std::out_of_range("Position out of map bounds");
        }
        return m_map.at(pos.y() * m_size.x() + pos.x());
    }

    Tile &getTile(int x, int y)
    {
        if (x >= m_size.x() || y >= m_size.y()) {
            throw std::out_of_range("Position out of map bounds");
        }
        return m_map.at(y * m_size.x() + x);
    }

    std::vector<Player> &getPlayers()
    {
        return m_players;
    }

    std::vector<Egg> &getEggs()
    {
        return m_eggs;
    }

    Pos<int, 2> getSize() const
    {
        return m_size;
    }

    void resize(int x, int y)
    {
        m_map.resize(x * y);
        m_size = {x, y};
    }

    void resize(const Pos<int, 2> &size)
    {
        m_map.resize(size.x() * size.y());
        m_size = size;
    }

  private:
    std::vector<Tile> m_map;
    std::vector<Player> m_players;
    std::vector<Egg> m_eggs;
    Pos<int, 2> m_size;
};

} // namespace Data
} // namespace GUI
