/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Inventory
*/

#pragma once

#include <cstddef>

namespace GUI {

class Inventory {
  public:
    Inventory(): food(0), q1(0), q2(0), q3(0), q4(0), q5(0), q6(0) {};

    size_t food;
    size_t q1, q2, q3, q4, q5, q6;
};
} // namespace GUI
