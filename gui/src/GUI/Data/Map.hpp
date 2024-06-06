/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Map
*/

#pragma once

#include <vector>
#include <memory>

#include "Egg.hpp"
#include "Player.hpp"
#include "Pos.hpp"
#include "Tile.hpp"
#include "../InfoBox.hpp"

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

    void checkCollision(int start_x, int start_y, int end_x, int end_y, InfoBox &infoBox);
    void displayTacticalView(int start_x, int start_y, int end_x, int end_y, const InfoBox &info) const;

  private:
    std::vector<std::shared_ptr<Tile>> m_map;
    std::vector<std::shared_ptr<Player>> m_players;
    std::vector<std::shared_ptr<Egg>> m_eggs;
    Pos<int, 2> m_size;
};

} // namespace Data
} // namespace GUI
