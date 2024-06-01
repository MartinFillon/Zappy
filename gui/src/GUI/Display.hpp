/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Display
*/

#pragma once

#include <raylib.h>
#include <string>
#include <tuple>
#include <vector>

#include "../Network/Handler.hpp"
#include "Data/Map.hpp"
#include "ServerMessageHandler.hpp"
#include "define.hpp"

namespace GUI {

class ServerMessageHandler;

class Display {
  public:
    Display(Network::Handler &networkHandler, bool debug, int width = 1920, int height = 1080);
    ~Display();
    void run();

    Data::Map &getMap()
    {
        return map;
    }

    void setTimeUnit(int time)
    {
        timeUnit = time;
    }

    void setEndGame(std::vector<std::string> message, bool end = true)
    {
        endGame = end;
        endGameMessage = message;
    }

    int getTimeUnit() const
    {
        return timeUnit;
    }

    void addMessage(std::string message, int user = SERVER)
    {
        messages.push_back(std::make_tuple(std::chrono::steady_clock::now(), user, message));
    }

    std::vector<std::string> team;

  private:
    void handleServerMessage(std::string &message);
    void resize();

    Network::Handler &networkHandler;
    ServerMessageHandler serverMessageHandler;
    bool debug;
    Data::Map map;
    int timeUnit;
    bool endGame;
    std::vector<std::string> endGameMessage;
    std::vector<std::tuple<std::chrono::time_point<std::chrono::steady_clock>, int, std::string>> messages;

    int offsetX, offsetY, newWidth, newHeight;
};

} // namespace GUI
