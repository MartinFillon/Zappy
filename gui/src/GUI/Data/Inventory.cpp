/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Inventory
*/


#include "Inventory.hpp"
#include <stdexcept>

namespace GUI {
namespace Data {

void Inventory::update(size_t q0, size_t q1, size_t q2, size_t q3, size_t q4, size_t q5, size_t q6)
{
    inv[0] = q0;
    inv[1] = q1;
    inv[2] = q2;
    inv[3] = q3;
    inv[4] = q4;
    inv[5] = q5;
    inv[6] = q6;
}

void Inventory::update(const std::array<size_t, 7> &new_inv)
{
    inv = new_inv;
}

void Inventory::update(int ressourceType, size_t quantity)
{
    if (ressourceType >= 7) {
        throw std::out_of_range("Ressource type out of range");
    }
    inv[ressourceType] = quantity;
}

bool Inventory::loot(int ressourceType, Inventory &other, size_t quantity)
{
    if (ressourceType >= 7) {
        throw std::out_of_range("Ressource type out of range");
    }
    if (other[ressourceType] < quantity) {
        return false;
    }
    other[ressourceType] -= quantity;
    inv[ressourceType] += quantity;
    return true;
}

bool Inventory::drop(int ressourceType, Inventory &other, size_t quantity)
{
    if (ressourceType >= 7) {
        throw std::out_of_range("Ressource type out of range");
    }
    if (inv[ressourceType] < quantity) {
        return false;
    }
    inv[ressourceType] -= quantity;
    other[ressourceType] += quantity;
    return true;
}

bool Inventory::dropAll(Inventory &other)
{
    for (size_t i = 0; i < 7; i++) {
        other[i] += inv[i];
        inv[i] = 0;
    }
    return true;
}

size_t &Inventory::operator[](size_t index)
{
    if (index >= 7) {
        throw std::out_of_range("Index out of range");
    }
    return inv[index];
}
} // namespace Data
} // namespace GUI
