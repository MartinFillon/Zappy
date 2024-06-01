/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Pos
*/

#pragma once

#include <algorithm>
#include <array>
#include <iostream>
#include <stdexcept>
#include <initializer_list>

template <typename T, std::size_t N>
class Pos {
  public:
    Pos(std::initializer_list<T> init)
    {
        if (init.size() != N) {
            throw std::invalid_argument("Initializer list size must match the number of dimensions");
        }
        std::copy(init.begin(), init.end(), coords.begin());
    }

    T &operator[](std::size_t index)
    {
        if (index >= N) {
            throw std::out_of_range("Index out of range");
        }
        return coords[index];
    }

    const T &operator[](std::size_t index) const
    {
        if (index >= N) {
            throw std::out_of_range("Index out of range");
        }
        return coords[index];
    }

    T &x()
    {
        static_assert(N > 0, "x coordinate is not available for this dimension");
        return coords[0];
    }

    const T &x() const
    {
        static_assert(N > 0, "x coordinate is not available for this dimension");
        return coords[0];
    }

    T &y()
    {
        static_assert(N > 1, "y coordinate is not available for this dimension");
        return coords[1];
    }

    const T &y() const
    {
        static_assert(N > 1, "y coordinate is not available for this dimension");
        return coords[1];
    }

    T &z()
    {
        static_assert(N > 2, "z coordinate is not available for this dimension");
        return coords[2];
    }

    const T &z() const
    {
        static_assert(N > 2, "z coordinate is not available for this dimension");
        return coords[2];
    }

  private:
    std::array<T, N> coords;
};

template <typename T, std::size_t N>
std::ostream &operator<<(std::ostream &os, const Pos<T, N> &pos)
{
    os << "(";
    for (std::size_t i = 0; i < N; ++i) {
        os << pos.coords[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << ")";
    return os;
}
