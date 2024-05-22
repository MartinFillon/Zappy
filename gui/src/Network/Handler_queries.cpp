/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** cmd
*/

#include "Handler.hpp"

namespace Network {
void Handler::requestMapSize()
{
    sendMessage("msz");
}

void Handler::requestTileContent(int x, int y)
{
    sendMessage("bct " + std::to_string(x) + " " + std::to_string(y));
}

void Handler::requestMapContent()
{
    sendMessage("mct");
}

void Handler::requestTeamNames()
{
    sendMessage("tna");
}

void Handler::requestPlayerPosition(int playerNumber)
{
    sendMessage("ppo #" + std::to_string(playerNumber));
}

void Handler::requestPlayerLevel(int playerNumber)
{
    sendMessage("plv #" + std::to_string(playerNumber));
}

void Handler::requestPlayerInventory(int playerNumber)
{
    sendMessage("pin #" + std::to_string(playerNumber));
}

void Handler::sendBroadcast(const std::string &message)
{
    sendMessage("pbc " + message);
}

void Handler::requestTimeUnit()
{
    sendMessage("sgt");
}

void Handler::modifyTimeUnit(int t)
{
    sendMessage("sst " + std::to_string(t));
}
} // namespace Network
