/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Map
*/

#pragma once

#include <memory>
#include <vector>
#include <raylib.h>

#include "../InfoBox.hpp"
#include "Egg.hpp"
#include "Player.hpp"
#include "Pos.hpp"
#include "Tile.hpp"
#include "../ModelManager/RessourcesManager.hpp"

namespace GUI {
namespace Data {

class Map {
  public:
    Map(int x, int y);
    Map(const Pos<int, 2> &pos);

    Tile &getTile(const Pos<int, 2> &pos);
    Tile &getTile(int x, int y);
    Tile getTile(const Pos<int, 2> &pos) const;
    Tile getTile(int x, int y) const;
    std::vector<std::shared_ptr<Player>> &getPlayers();
    std::vector<std::shared_ptr<Egg>> &getEggs();

    Pos<int, 2> getSize() const;
    void resize(int x, int y);
    void resize(const Pos<int, 2> &size);

    void checkCollision(InfoBox &infoBox) const;
    void checkCollision3D(InfoBox &infoBox, const Camera3D &cam) const;
    void displayTacticalView(int start_x, int start_y, int end_x, int end_y, const InfoBox &info) const;
    void displayTacticalView3D(const InfoBox &info, Camera3D &cam, bool &showCursor, bool &isCameraFree) const;

  private:
    std::vector<std::shared_ptr<Tile>> m_map;
    std::vector<std::shared_ptr<Player>> m_players;
    std::vector<std::shared_ptr<Egg>> m_eggs;
    Pos<int, 2> m_size;
    mutable int x, y, end_x, end_y;
    mutable RessourcesManager qm;
};

} // namespace Data
} // namespace GUI
