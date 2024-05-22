/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ServerMessageHandler
*/

#pragma once
#include <functional>
#include <string>
#include "Display.hpp"
#include <unordered_map>

class Display;

class ServerMessageHandler {
  public:
    ServerMessageHandler(bool debug, Display &display);

    void handleServerMessage(const std::string &message);

  private:
    void handleMapSize(const std::string &message);
    void handleTileContent(const std::string &message);
    void handleTeamNames(const std::string &message);
    void handlePlayerPosition(const std::string &message);
    void handlePlayerLevel(const std::string &message);
    void handlePlayerInventory(const std::string &message);
    void handleExpulsion(const std::string &message);
    void handleBroadcast(const std::string &message);
    void handleIncantationStart(const std::string &message);
    void handleIncantationEnd(const std::string &message);
    void handleEggLaying(const std::string &message);
    void handleResourceDrop(const std::string &message);
    void handleResourceCollect(const std::string &message);
    void handlePlayerDeath(const std::string &message);
    void handleEggLaid(const std::string &message);
    void handleEggHatch(const std::string &message);
    void handlePlayerConnectEgg(const std::string &message);
    void handleEggDeath(const std::string &message);
    void handleTimeUnit(const std::string &message);
    void handleTimeUnitModification(const std::string &message);
    void handleEndGame(const std::string &message);
    void handleMessageFromServer(const std::string &message);
    void handleUnknownCommand(const std::string &message);
    void handleCommandParameter(const std::string &message);

    bool debug;
    Display &display;
    std::unordered_map<std::string, std::function<void(const std::string &)>>
        commandHandlers;
};
