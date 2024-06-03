/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Player
*/

#pragma once

#include <chrono>
#include "Tile.hpp"

#include "ASelectItem.hpp"

namespace GUI {
namespace Data {

class Player : public ASelectItem {
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

    enum class Direction { UNDEFINED, UP, RIGHT, DOWN, LEFT };

    Player(int x, int y, Direction direction, int id, const std::string &team, int level = 1, bool is_hatched = false);
    Player(
        const Pos<int, 2> &pos,
        Direction direction,
        int id,
        const std::string &team,
        int level = 1,
        bool is_hatched = false
    );

    int getLevel() const;
    int getId() const;
    const std::string &getTeam() const;
    Direction getOrientation() const;

    void setLevel(int level);
    void setPosition(int x, int y, Direction direction);

    bool isHatched() const;
    void spawn();

    void loot(Tile &tile, int ressourceType, size_t quantity = 1);
    void drop(Tile &tile, int ressourceType, size_t quantity = 1);

    Incantation &getIncantation();

    std::vector<std::string> getStringInfo() const override;

  private:
    int m_id;
    std::string m_team;
    int m_level;
    bool m_is_hatched;
    Incantation m_incantation;
    Direction m_orientation;
};

} // namespace Data
} // namespace GUI
