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
            Map() = default;
            ~Map() = default;

            Tile &getTile(Pos<size_t> &pos) {
                m_map.at(pos.x % m_size.);
            };

        private:
            std::vector<Tile> m_map;
            std::vector<Player> m_players;
            std::vector<Egg> m_egg;
            Pos<size_t> m_size;
    };
}
