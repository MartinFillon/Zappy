/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Player
*/

#include "Player.hpp"

namespace GUI {
namespace Data {

Player::Incantation::Incantation() : started(false), duration(0), startTime(), target({0, 0}) {}

void Player::Incantation::start(int duration, int x, int y)
{
    this->duration = duration;
    target = {x, y};
    startTime = std::chrono::steady_clock::now();
    started = true;
}

void Player::Incantation::end()
{
    started = false;
}

bool Player::Incantation::isStarted() const
{
    return started;
}

int Player::Incantation::timeLeft() const
{
    if (!started)
        return 0;
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
    return std::max(0, duration - static_cast<int>(elapsed));
}

double Player::Incantation::progress() const
{
    if (!started)
        return 0.0;
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
    return std::min(1.0, static_cast<double>(elapsed) / duration);
}

Pos<int, 2> Player::Incantation::getTarget() const
{
    return target;
}

Player::Player(int x, int y, Direction direction, int id, const std::string &team, int level, bool is_hatched)
    : ASelectItem(x, y), m_id(id), m_team(team), m_level(level), m_is_hatched(is_hatched), m_orientation(direction)
{
}

Player::Player(const Pos<int, 2> &pos, Direction direction, int id, const std::string &team, int level, bool is_hatched)
    : ASelectItem(pos), m_id(id), m_team(team), m_level(level), m_is_hatched(is_hatched), m_orientation(direction)
{
}

int Player::getLevel() const
{
    return m_level;
}

void Player::setLevel(int level)
{
    m_level = level;
}

int Player::getId() const
{
    return m_id;
}

const std::string &Player::getTeam() const
{
    return m_team;
}

Player::Direction Player::getOrientation() const
{
    return m_orientation;
}

void Player::setPosition(int x, int y, Direction direction)
{
    m_pos = Pos<int, 2>({x, y});
    m_orientation = direction;
}

bool Player::isHatched() const
{
    return m_is_hatched;
}

void Player::spawn()
{
    m_is_hatched = true;
}

void Player::loot(Tile &tile, int ressourceType, size_t quantity)
{
    m_inv.loot(ressourceType, tile.getInventory(), quantity);
}

void Player::drop(Tile &tile, int ressourceType, size_t quantity)
{
    m_inv.drop(ressourceType, tile.getInventory(), quantity);
}

Player::Incantation &Player::getIncantation()
{
    return m_incantation;
}

#include <unistd.h>

std::vector<std::string> Player::getStringInfo() const
{
    std::vector<std::string> infoList = {
        "--Player-Info--",
        "",
        std::string("[Team]: ").append(m_team),
        std::string("[Id]: ").append(std::to_string(m_id)),
        std::string("[Level]: ").append(std::to_string(m_level))
    };
    return infoList;
}

} // namespace Data
} // namespace GUI
