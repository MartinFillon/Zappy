/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Tile
*/

#pragma once

#include "Inventory.hpp"

namespace GUI {

    class Tile {
        public:
            Tile() = default;
            ~Tile() = default;

        private:
            Inventory m_inv;
    };
}
