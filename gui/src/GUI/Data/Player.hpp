/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Player
*/

#pragma once

#include <chrono>
#include "Inventory.hpp"
#include "Pos.hpp"
#include "Tile.hpp"

namespace GUI {
namespace Data {

class Player {
  public:
    class Incantation {
      public:
        Incantation();

        void start(int duration, int x, int y);
        void end();

        bool isStarted() const;
        int timeLeft() const;
        double progress() const;
        Pos<int, 2> getTarget() const;

      private:
        bool started;
        int duration;
        std::chrono::time_point<std::chrono::steady_clock> startTime;
        Pos<int, 2> target;
    };

    Player(int x, int y, int id, const std::string &team, int level = 1, bool is_hatched = false);
    Player(const Pos<int, 2> &pos, int id, const std::string &team, int level = 1, bool is_hatched = false);

    Pos<int, 2> getPos() const;
    Inventory &getInventory();
    int getLevel() const;
    int getId() const;
    const std::string &getTeam() const;

    void setLevel(int level);
    void setPosition(int x, int y);

    bool isHatched() const;
    void spawn();

    void loot(Tile &tile, int ressourceType, size_t quantity = 1);
    void drop(Tile &tile, int ressourceType, size_t quantity = 1);

    Incantation &getIncantation();

  private:
    Pos<int, 2> m_pos;
    Inventory m_inv;
    int m_id;
    std::string m_team;
    int m_level;
    bool m_is_hatched;
    Incantation m_incantation;
    int m_orientation;
};

} // namespace Data
} // namespace GUI
