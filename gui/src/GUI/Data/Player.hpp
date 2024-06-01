/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Player
*/

#pragma once

#include "Inventory.hpp"
#include "Pos.hpp"
#include "Tile.hpp"

namespace GUI {
namespace Data {

class Player {
public:
    Player(int x, int y, int id, const std::string &team) : m_pos({x, y}), m_id(id), m_team(team), m_level(1), m_is_hatched(false) {}

    Player(const Pos<int, 2> &pos, int id, const std::string &team) : m_pos(pos), m_id(id), m_team(team), m_level(1), m_is_hatched(false) {}

    Pos<int, 2> getPos() const
    {
        return m_pos;
    }

    Inventory &getInventory()
    {
        return m_inv;
    }

    int getLevel() const
    {
        return m_level;
    }

    void setLevel(int level)
    {
        m_level = level;
    }

    int getId() const
    {
        return m_id;
    }

    const std::string &getTeam() const
    {
        return m_team;
    }

    void setPosition(int x, int y)
    {
        m_pos = Pos<int, 2>({x, y});
    }

    bool isHatched() const
    {
        return m_is_hatched;
    }

    void spawn()
    {
        m_is_hatched = true;
    }

    void loot(Tile &tile, int ressourceType, size_t quantity = 1)
    {
        m_inv.loot(ressourceType, tile.getRessources(), quantity);
    }

    void drop(Tile &tile, int ressourceType, size_t quantity = 1)
    {
        m_inv.drop(ressourceType, tile.getRessources(), quantity);
    }

private:
    Pos<int, 2> m_pos;
    Inventory m_inv;
    int m_id;
    std::string m_team;
    int m_level;
    bool m_is_hatched;
};

} // namespace Data
} // namespace GUI
