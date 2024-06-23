/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Map
*/

#pragma once

#include <memory>
#include <raylib.h>
#include <vector>

#include "../../Network/Handler.hpp"
#include "../ModelManager/RessourcesManager.hpp"
#include "../UI/InfoBox.hpp"
#include "Egg.hpp"
#include "Player.hpp"
#include "Pos.hpp"
#include "Tile.hpp"

#define SIZE_STEP_1 3
#define SIZE_STEP_2 5

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

    void collision(UI::InfoBox &infoBox, Network::Handler &handler) const;
    void collision3D(UI::InfoBox &infoBox, const Camera3D &cam, Network::Handler &handler) const;
    void display2D(int start_x, int start_y, int end_x, int end_y, const UI::InfoBox &info) const;
    void display3D(const UI::InfoBox &info) const;

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
