/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Egg
*/

#pragma once

#include <vector>
#include <string>

#include "Pos.hpp"
#include "Inventory.hpp"

namespace GUI {
namespace Data {

class ISelectItem {
  public:
    virtual std::vector<std::string> getStringInfo() const = 0;
    virtual Inventory &getInventory() = 0;
    virtual Inventory getInventory() const = 0;
    virtual Pos<int, 2> getPos() const = 0;
};

} // namespace Data
} // namespace GUI
