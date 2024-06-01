/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Inventory
*/

#pragma once

#include <array>
#include <cstddef>
#include <stdexcept>
#include <string>

namespace GUI {
namespace Data {
class Inventory {
  public:
    Inventory() : inv({0, 0, 0, 0, 0, 0, 0}){};
    Inventory(size_t q0, size_t q1, size_t q2, size_t q3, size_t q4, size_t q5, size_t q6)
        : inv({q0, q1, q2, q3, q4, q5, q6}){};
    ~Inventory() = default;

    void update(size_t q0, size_t q1, size_t q2, size_t q3, size_t q4, size_t q5, size_t q6)
    {
        inv[0] = q0;
        inv[1] = q1;
        inv[2] = q2;
        inv[3] = q3;
        inv[4] = q4;
        inv[5] = q5;
        inv[6] = q6;
    }

    void update(const std::array<size_t, 7> &new_inv)
    {
        inv = new_inv;
    }

    void update(int ressourceType, size_t quantity)
    {
        if (ressourceType >= 7) {
            throw std::out_of_range("Ressource type out of range");
        }
        inv[ressourceType] = quantity;
    }

    bool loot(int ressourceType, Inventory &other, size_t quantity = 1)
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

    bool drop(int ressourceType, Inventory &other, size_t quantity = 1)
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

    bool dropAll(Inventory &other)
    {
        for (size_t i = 0; i < 7; i++) {
            other[i] += inv[i];
            inv[i] = 0;
        }
        return true;
    }

    size_t &operator[](size_t index)
    {
        if (index >= 7) {
            throw std::out_of_range("Index out of range");
        }
        return inv[index];
    }

    std::array<size_t, 7> inv;
};
} // namespace Data
} // namespace GUI
