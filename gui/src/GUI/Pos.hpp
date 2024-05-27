/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Pos
*/

#pragma once

template <typename T>
class Pos {
  public:
    Pos(T x, T y) : x(x), y(y) {}

    T x, y;
};
