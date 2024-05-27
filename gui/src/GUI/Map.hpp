/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Map
*/

#pragma once

#include <vector>

#include "Tile.hpp"
#include "Player.hpp"
#include "Pos.hpp"

namespace GUI {

    class Map {
        public:
            Map(int &x, int &y): m_size(Pos<int>(x, y)) {};
            Map(Pos<int> &pos): m_size(pos) {};
            ~Map() = default;

            Tile &getTile(Pos<int> &pos) {
                m_map.at(pos.y * m_size.x + pos.x);
            };

        private:
            std::vector<Tile> m_map;
            std::vector<Player> m_players;
            std::vector<Egg> m_egg;
            Pos<int> m_size;
    };
}
