/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Mapp
*/

#include "Map.hpp"

namespace GUI {
namespace Data {

Map::Map(int x, int y) : m_size({x, y})
{
    m_map.resize(x * y);
}

Map::Map(const Pos<int, 2> &pos) : m_size(pos)
{
    m_map.resize(pos.x() * pos.y());
}

Tile &Map::getTile(const Pos<int, 2> &pos)
{
    if (pos.x() >= m_size.x() || pos.y() >= m_size.y()) {
        throw std::out_of_range("Position out of map bounds");
    }
    return m_map.at(pos.y() * m_size.x() + pos.x());
}

Tile &Map::getTile(int x, int y)
{
    if (x >= m_size.x() || y >= m_size.y()) {
        throw std::out_of_range("Position out of map bounds");
    }
    return m_map.at(y * m_size.x() + x);
}

std::vector<Player> &Map::getPlayers()
{
    return m_players;
}

std::vector<Egg> &Map::getEggs()
{
    return m_eggs;
}

Pos<int, 2> Map::getSize() const
{
    return m_size;
}

void Map::resize(int x, int y)
{
    m_map.resize(x * y);
    m_size = {x, y};
}

void Map::resize(const Pos<int, 2> &size)
{
    m_map.resize(size.x() * size.y());
    m_size = size;
}

} // namespace Data
} // namespace GUI
