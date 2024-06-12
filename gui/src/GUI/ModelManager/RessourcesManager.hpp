/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** RessourcesManager
*/

#pragma once
#include <cstddef>
#include <map>
#include <string>
#include "Model3D.hpp"

#define L1 "gui/assets/rocks/L_rocks_01.glb"
#define L2 "gui/assets/rocks/L_rocks_02.glb"
#define L3 "gui/assets/rocks/L_rocks_03.glb"
#define L4 "gui/assets/rocks/L_rocks_04.glb"
#define L5 "gui/assets/rocks/L_rocks_05.glb"
#define L6 "gui/assets/rocks/L_rocks_06.glb"
#define M1 "gui/assets/rocks/M_rocks_01.glb"
#define M2 "gui/assets/rocks/M_rocks_02.glb"
#define M3 "gui/assets/rocks/M_rocks_03.glb"
#define M4 "gui/assets/rocks/M_rocks_04.glb"
#define M5 "gui/assets/rocks/M_rocks_05.glb"
#define M6 "gui/assets/rocks/M_rocks_06.glb"
#define S1 "gui/assets/rocks/M_rocks_01.glb"
#define S2 "gui/assets/rocks/M_rocks_02.glb"
#define S3 "gui/assets/rocks/M_rocks_03.glb"
#define S4 "gui/assets/rocks/M_rocks_04.glb"
#define S5 "gui/assets/rocks/M_rocks_05.glb"
#define S6 "gui/assets/rocks/M_rocks_06.glb"

class RessourcesManager {
  public:
    RessourcesManager() : _map() {}

    ~RessourcesManager() = default;

    void init()
    {
        _map[{0, 1}] = Model3D(S1);
        _map[{0, 2}] = Model3D(S2);
        _map[{0, 3}] = Model3D(S3);
        _map[{0, 4}] = Model3D(S4);
        _map[{0, 5}] = Model3D(S5);
        _map[{0, 6}] = Model3D(S6);
        _map[{1, 1}] = Model3D(M1);
        _map[{1, 2}] = Model3D(M2);
        _map[{1, 3}] = Model3D(M3);
        _map[{1, 4}] = Model3D(M4);
        _map[{1, 5}] = Model3D(M5);
        _map[{1, 6}] = Model3D(M6);
        _map[{2, 1}] = Model3D(L1);
        _map[{2, 2}] = Model3D(L2);
        _map[{2, 3}] = Model3D(L3);
        _map[{2, 4}] = Model3D(L4);
        _map[{2, 5}] = Model3D(L5);
        _map[{2, 6}] = Model3D(L6);
    }

    size_t getSize()
    {
        return _map.size();
    }

    void Draw(int size, int type, float x, float y, float tileSize = 1.f)
    {
        _map[{size, type}].Draw({x * tileSize, 2, y * tileSize}, {1, 1, 1}, {1, 1, 1}, 0);
    }

  protected:
  private:
    std::map<std::tuple<int, int>, Model3D> _map;
};
