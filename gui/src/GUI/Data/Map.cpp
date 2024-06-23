/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Map
*/

#include "Map.hpp"
#include <memory>
#include <raylib.h>
#include <vector>

namespace GUI {
namespace Data {

Map::Map(int x, int y) : m_size({x, y}), x(0), y(0), end_x(0), end_y(0)
{
    resize(x, y);
}

Map::Map(const Pos<int, 2> &pos) : m_size(pos), x(0), y(0), end_x(0), end_y(0)
{
    resize(pos);
}

Tile &Map::getTile(const Pos<int, 2> &pos)
{
    if (pos.x() >= m_size.x() || pos.y() >= m_size.y()) {
        throw std::out_of_range("Position out of map bounds");
    }
    return *m_map.at(pos.y() * m_size.x() + pos.x());
}

Tile &Map::getTile(int x, int y)
{
    if (x >= m_size.x() || y >= m_size.y()) {
        throw std::out_of_range("Position out of map bounds");
    }
    return *m_map.at(y * m_size.x() + x);
}

Tile Map::getTile(const Pos<int, 2> &pos) const
{
    if (pos.x() >= m_size.x() || pos.y() >= m_size.y()) {
        throw std::out_of_range("Position out of map bounds");
    }
    return *m_map.at(pos.y() * m_size.x() + pos.x());
}

Tile Map::getTile(int x, int y) const
{
    if (x >= m_size.x() || y >= m_size.y()) {
        throw std::out_of_range("Position out of map bounds");
    }
    Tile tile = *m_map.at(y * m_size.x() + x);
    if (x != tile.getPos().x() && y != tile.getPos().y())
        std::cout << "wanted (" << x << ", " << y << ") | me: ()" << tile.getPos().x() << ", " << tile.getPos().y()
                  << ")" << std::endl;
    return tile;
}

std::vector<std::shared_ptr<Player>> &Map::getPlayers()
{
    return m_players;
}

const std::vector<std::shared_ptr<Player>> &Map::getPlayers() const
{
    return m_players;
}

std::vector<std::shared_ptr<Egg>> &Map::getEggs()
{
    return m_eggs;
}

Pos<int, 2> Map::getSize() const
{
    return m_size;
}

void Map::resize(int x, int y)
{
    int size_map = static_cast<int>(m_map.size());

    if (size_map > x * y || size_map < x * y) {
        m_map.clear();
        for (int y = 0; y < x; y++) {
            for (int i = 0; i < x; i++) {
                m_map.push_back(std::make_shared<Tile>(i, y));
            }
        }
        m_size = {x, y};
    }
}

void Map::resize(const Pos<int, 2> &size)
{
    int size_map = static_cast<int>(m_map.size());
    int x = size.x();
    int y = size.y();

    if (size_map > x * y || size_map < x * y) {
        m_map.clear();
        for (int y = 0; y < x; y++) {
            for (int i = 0; i < x; i++) {
                m_map.push_back(std::make_shared<Tile>(i, y));
            }
        }
        m_size = {x, y};
    }
}

std::vector<std::shared_ptr<Tile>> &Map::getTiles()
{
    return m_map;
}

void Map::set2DDisplay(int start_x, int start_y, int end_x, int end_y)
{
    this->x = start_x;
    this->y = start_y;
    this->end_x = end_x;
    this->end_y = end_y;
}

} // namespace Data
} // namespace GUI
