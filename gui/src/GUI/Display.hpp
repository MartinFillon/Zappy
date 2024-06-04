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
#include "MessageBox.hpp"
#include "InfoBox.hpp"
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
        messageBox.addMessage(message, user);
    }

    std::vector<std::string> team;

  private:
    void handleEvent();
    void handleServerMessage(std::string &message);
    void resize();
    void displayMessages(int x, int y, int width, int height);

    Network::Handler &networkHandler;
    ServerMessageHandler serverMessageHandler;
    bool debug;
    Data::Map map;
    int timeUnit;
    bool endGame;
    std::vector<std::string> endGameMessage;
    int offsetX, offsetY, newWidth, newHeight;
    MessageBox messageBox;
    InfoBox infoBox;
};

} // namespace GUI
