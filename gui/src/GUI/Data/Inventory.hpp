/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Inventory
*/

#pragma once

#include <cstddef>

namespace GUI {
namespace Data {
class Inventory {
  public:
    Inventory() : food(0), q1(0), q2(0), q3(0), q4(0), q5(0), q6(0){};

    void update(int q0, int q1, int q2, int q3, int q4, int q5, int q6)
    {
        food = q0;
        this->q1 = q1;
        this->q2 = q2;
        this->q3 = q3;
        this->q4 = q4;
        this->q5 = q5;
        this->q6 = q6;
    }

    size_t food;
    size_t q1, q2, q3, q4, q5, q6;
};
} // namespace Data
} // namespace GUI
