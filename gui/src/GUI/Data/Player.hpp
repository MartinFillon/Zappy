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
        Incantation() : started(false), duration(0), startTime(), target({0, 0}) {}

        void start(int duration, int x, int y)
        {
            this->duration = duration;
            target = {x, y};
            startTime = std::chrono::steady_clock::now();
            started = true;
        }

        void end()
        {
            started = false;
        }

        bool isStarted() const
        {
            return started;
        }

        int timeLeft() const
        {
            if (!started)
                return 0;
            auto now = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
            return std::max(0, duration - static_cast<int>(elapsed));
        }

        double progress() const
        {
            if (!started)
                return 0.0;
            auto now = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
            return std::min(1.0, static_cast<double>(elapsed) / duration);
        }

        Pos<int, 2> getTarget() const
        {
            return target;
        }

      private:
        bool started;
        int duration;
        std::chrono::time_point<std::chrono::steady_clock> startTime;
        Pos<int, 2> target;
    };

    Player(int x, int y, int id, const std::string &team, int level = 1, bool is_hatched = false)
        : m_pos({x, y}), m_id(id), m_team(team), m_level(level), m_is_hatched(is_hatched)
    {
    }

    Player(const Pos<int, 2> &pos, int id, const std::string &team, int level = 1, bool is_hatched = false)
        : m_pos(pos), m_id(id), m_team(team), m_level(level), m_is_hatched(is_hatched)
    {
    }

    Pos<int, 2> getPos() const
    {
        return m_pos;
    }

    Inventory &getInventory()
    {
        return m_inv;
    }

    int getLevel() const
    {
        return m_level;
    }

    void setLevel(int level)
    {
        m_level = level;
    }

    int getId() const
    {
        return m_id;
    }

    const std::string &getTeam() const
    {
        return m_team;
    }

    void setPosition(int x, int y)
    {
        m_pos = Pos<int, 2>({x, y});
    }

    bool isHatched() const
    {
        return m_is_hatched;
    }

    void spawn()
    {
        m_is_hatched = true;
    }

    void loot(Tile &tile, int ressourceType, size_t quantity = 1)
    {
        m_inv.loot(ressourceType, tile.getRessources(), quantity);
    }

    void drop(Tile &tile, int ressourceType, size_t quantity = 1)
    {
        m_inv.drop(ressourceType, tile.getRessources(), quantity);
    }

    Incantation &getIncantation()
    {
        return m_incantation;
    }

  private:
    Pos<int, 2> m_pos;
    Inventory m_inv;
    int m_id;
    std::string m_team;
    int m_level;
    bool m_is_hatched;
    Incantation m_incantation;
};

} // namespace Data
} // namespace GUI
