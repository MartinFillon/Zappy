/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Display
*/

#pragma once

#include <raylib.h>
#include <string>
#include <memory>
#include <vector>

#include "../Network/Handler.hpp"
#include "Data/Map.hpp"
#include "ServerMessageHandler.hpp"

namespace GUI {

class ServerMessageHandler;

class Display {
  public:
    Display(Network::Handler &networkHandler, bool debug, int width = 800, int height = 450);
    ~Display();
    void run();

    Data::Map &getMap()
    {
        return map;
    }

    void updateTimeUnit(int time)
    {
        timeUnit = time;
    }

    std::vector<std::string> team;
  private:
    void handleServerMessage(std::string &message);

    Network::Handler &networkHandler;
    ServerMessageHandler serverMessageHandler;
    bool debug;
    Data::Map map;
    int timeUnit;
};
}; // namespace GUI
