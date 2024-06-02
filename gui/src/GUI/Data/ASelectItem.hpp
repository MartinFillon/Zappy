/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ISelectItem
*/

#pragma once

#include "ISelectItem.hpp"

namespace GUI {
namespace Data {

class ASelectItem : public ISelectItem {
  public:
    ASelectItem(const Pos<int, 2> &pos) : m_pos(pos) {};
    ASelectItem(int x, int y) : m_pos({x, y}) {};

    Inventory &getInventory() override {
        return m_inv;
    };

    Inventory getInventory() const override {
        return m_inv;
    };

    Pos<int, 2> getPos() const override
    {
        return m_pos;
    }

  protected:
    Pos<int, 2> m_pos;
    Inventory m_inv;
};

} // namespace Data
} // namespace GUI
