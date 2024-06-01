/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Inventory
*/

#pragma once

#include <array>
#include <cstddef>

namespace GUI {
namespace Data {
class Inventory {
  public:
    Inventory() : inv({0, 0, 0, 0, 0, 0, 0}){};
    Inventory(size_t q0, size_t q1, size_t q2, size_t q3, size_t q4, size_t q5, size_t q6)
        : inv({q0, q1, q2, q3, q4, q5, q6}){};
    ~Inventory() = default;

    void update(size_t q0, size_t q1, size_t q2, size_t q3, size_t q4, size_t q5, size_t q6);
    void update(const std::array<size_t, 7> &new_inv);
    void update(int ressourceType, size_t quantity);

    bool loot(int ressourceType, Inventory &other, size_t quantity = 1);
    bool drop(int ressourceType, Inventory &other, size_t quantity = 1);
    bool dropAll(Inventory &other);

    size_t &operator[](size_t index);

    std::array<size_t, 7> inv;
};
} // namespace Data
} // namespace GUI
