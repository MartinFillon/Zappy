/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Player
*/

#pragma once

#include "Inventory.hpp"
#include "Pos.hpp"
#include "Egg.hpp"

namespace GUI {

    class Player {
        public:
            Player(int &x, int &y, int &id): m_pos(Pos<int>(x, y)), m_id(id) {};
            Player(Pos<int> &pos, int &id): m_pos(pos), m_id(id) {};
            ~Player() = default;

            Pos<int> getPos() { return m_pos; };
            Inventory getRessources() { return m_inv; };
            int getLevel() { return m_level; };
            int getId() { return m_id; };

        private:
            Pos<int> m_pos;
            Inventory m_inv;
            int m_level;
            int m_id;
    };

}
