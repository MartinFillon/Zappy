/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** cmd
*/

#include "NetworkHandler.hpp"

void NetworkHandler::requestMapSize()
{
    sendMessage("msz");
}

void NetworkHandler::requestTileContent(int x, int y)
{
    sendMessage("bct " + std::to_string(x) + " " + std::to_string(y));
}

void NetworkHandler::requestMapContent()
{
    sendMessage("mct");
}

void NetworkHandler::requestTeamNames()
{
    sendMessage("tna");
}

void NetworkHandler::requestPlayerPosition(int playerNumber)
{
    sendMessage("ppo #" + std::to_string(playerNumber));
}

void NetworkHandler::requestPlayerLevel(int playerNumber)
{
    sendMessage("plv #" + std::to_string(playerNumber));
}

void NetworkHandler::requestPlayerInventory(int playerNumber)
{
    sendMessage("pin #" + std::to_string(playerNumber));
}

void NetworkHandler::sendBroadcast(const std::string &message)
{
    sendMessage("pbc " + message);
}

void NetworkHandler::requestTimeUnit()
{
    sendMessage("sgt");
}

void NetworkHandler::modifyTimeUnit(int t)
{
    sendMessage("sst " + std::to_string(t));
}
