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

Player::Player(int x, int y, int id, const std::string &team, int level, bool is_hatched)
    : m_pos({x, y}), m_id(id), m_team(team), m_level(level), m_is_hatched(is_hatched)
{
}

Player::Player(const Pos<int, 2> &pos, int id, const std::string &team, int level, bool is_hatched)
    : m_pos(pos), m_id(id), m_team(team), m_level(level), m_is_hatched(is_hatched)
{
}

Pos<int, 2> Player::getPos() const
{
    return m_pos;
}

Inventory &Player::getInventory()
{
    return m_inv;
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

void Player::setPosition(int x, int y)
{
    m_pos = Pos<int, 2>({x, y});
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
    m_inv.loot(ressourceType, tile.getRessources(), quantity);
}

void Player::drop(Tile &tile, int ressourceType, size_t quantity)
{
    m_inv.drop(ressourceType, tile.getRessources(), quantity);
}

Player::Incantation &Player::getIncantation()
{
    return m_incantation;
}

} // namespace Data
} // namespace GUI
