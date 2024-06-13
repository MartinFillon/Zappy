/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** RessourcesManager
*/

#pragma once
#include <cmath>
#include <cstddef>
#include <map>
#include <string>
#include "Model3D.hpp"
#include "raymath.h"

#define L0 "gui/assets/food/L_food.glb"
#define L1 "gui/assets/rocks/L_rocks_01.glb"
#define L2 "gui/assets/rocks/L_rocks_02.glb"
#define L3 "gui/assets/rocks/L_rocks_03.glb"
#define L4 "gui/assets/rocks/L_rocks_04.glb"
#define L5 "gui/assets/rocks/L_rocks_05.glb"
#define L6 "gui/assets/rocks/L_rocks_06.glb"
#define M0 "gui/assets/food/M_food.glb"
#define M1 "gui/assets/rocks/M_rocks_01.glb"
#define M2 "gui/assets/rocks/M_rocks_02.glb"
#define M3 "gui/assets/rocks/M_rocks_03.glb"
#define M4 "gui/assets/rocks/M_rocks_04.glb"
#define M5 "gui/assets/rocks/M_rocks_05.glb"
#define M6 "gui/assets/rocks/M_rocks_06.glb"
#define S0 "gui/assets/food/S_food.glb"
#define S1 "gui/assets/rocks/S_rocks_01.glb"
#define S2 "gui/assets/rocks/S_rocks_02.glb"
#define S3 "gui/assets/rocks/S_rocks_03.glb"
#define S4 "gui/assets/rocks/S_rocks_04.glb"
#define S5 "gui/assets/rocks/S_rocks_05.glb"
#define S6 "gui/assets/rocks/S_rocks_06.glb"

class RessourcesManager {
  public:
    RessourcesManager() : _map() {}

    ~RessourcesManager() = default;

    void init()
    {
        _map[{0, 0}] = Model3D(S0);
        _map[{0, 1}] = Model3D(S1);
        _map[{0, 2}] = Model3D(S2);
        _map[{0, 3}] = Model3D(S3);
        _map[{0, 4}] = Model3D(S4);
        _map[{0, 5}] = Model3D(S5);
        _map[{0, 6}] = Model3D(S6);
        _map[{1, 0}] = Model3D(M0);
        _map[{1, 1}] = Model3D(M1);
        _map[{1, 2}] = Model3D(M2);
        _map[{1, 3}] = Model3D(M3);
        _map[{1, 4}] = Model3D(M4);
        _map[{1, 5}] = Model3D(M5);
        _map[{1, 6}] = Model3D(M6);
        _map[{2, 0}] = Model3D(L0);
        _map[{2, 1}] = Model3D(L1);
        _map[{2, 2}] = Model3D(L2);
        _map[{2, 3}] = Model3D(L3);
        _map[{2, 4}] = Model3D(L4);
        _map[{2, 5}] = Model3D(L5);
        _map[{2, 6}] = Model3D(L6);
        _resourcePositions[0] = {-0.4, -0.37};
        _resourcePositions[1] = {-0.43, 0.41};
        _resourcePositions[2] = {0.07, -0.24};
        _resourcePositions[3] = {0.21, 0.4};
        _resourcePositions[4] = {0.27, -0.0};
        _resourcePositions[5] = {-0.03, -0.39};
        _resourcePositions[6] = {-0.38, -0.22};
        _resourcePositions[7] = {0.41, 0.05};
        _resourcePositions[8] = {0.04, 0.36};
        for (int i = 0; i <= 2; i++) {
            _map[{i, 0}].model.transform = MatrixRotateXYZ((Vector3){DEG2RAD * 270, 0, 0});
        }
    }

    size_t getSize()
    {
        return _map.size();
    }

    void Draw(int size, int type, float x, float z, float tileSize = 1.f)
    {
        float y = tileSize / 2;
        float scale = tileSize / 10 * std::pow(1.1, (size + 1));
        float offsetX = _resourcePositions[((static_cast<int>(z + x) + type) % _resourcePositions.size())].first *
            ((static_cast<int>(z) % 3) ? 1 : -1) * ((static_cast<int>(z + x) % 6 >= 3) ? 1 : -1);
        float offsetZ = _resourcePositions[((static_cast<int>(z + x) + type) % _resourcePositions.size())].second *
            ((static_cast<int>(x) % 3) ? -1 : 1) * ((static_cast<int>(z + x) % 6 >= 3) ? 1 : -1);
        z = (z + offsetZ) * tileSize;
        x = (x + offsetX) * tileSize;
        y += 0.05 * size;
        if (type == 0) {
            scale *= 5;
            tileSize /= 2;
        } else {
            tileSize /= 10;
        }
        _map[{size, type}].Draw(
            {x, y, z}, {tileSize, scale, tileSize}, {0, (static_cast<int>(x) % 2) ? 1.f : -1.f, 0}, (x + z) * 7
        );
    }

  protected:
  private:
    std::map<std::tuple<int, int>, Model3D> _map;
    std::map<int, std::pair<float, float>> _resourcePositions;
};
