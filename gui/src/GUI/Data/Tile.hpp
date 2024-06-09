/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Tile
*/

#pragma once

#include "ASelectItem.hpp"

namespace GUI {
namespace Data {
class Tile : public ASelectItem {
  public:
    Tile(int x, int y): ASelectItem(x, y) {};
    Tile(const Pos<int, 2> &pos): ASelectItem(pos) {};
    ~Tile() = default;

    void updateRessources(int q0, int q1, int q2, int q3, int q4, int q5, int q6)
    {
        m_inv.update(q0, q1, q2, q3, q4, q5, q6);
    }

    std::vector<std::string> getStringInfo() const override
    {
        std::vector<std::string> infoList = {
            "--Tile-Info--",
            "",
            std::string("[x]: ").append(std::to_string(m_pos.x())),
            std::string("[y]: ").append(std::to_string(m_pos.y())),
        };
        return infoList;
    }
};
} // namespace Data
} // namespace GUI
