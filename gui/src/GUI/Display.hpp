/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Display
*/

#pragma once

#include <string>
#include <vector>

#include "../Network/Handler.hpp"
#include "Data/Map.hpp"
#include "MessageBox.hpp"
#include "TimeUnitInput.hpp"
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
        timeUnitInput.setTimeUnit(time);
    }

    void setEndGame(std::vector<std::string> message, bool end = true)
    {
        endGame = end;
        endGameMessage = message;
    }

    int getTimeUnit() const
    {
        return timeUnitInput.getTimeUnit();
    }

    void addMessage(std::string message, int user = SERVER)
    {
        if (user == SERVER)
            messageBox.addMessage(message, user);
        std::string team_str;
        for (auto &player : map.getPlayers()) {
            if (player->getId() == user) {
                team_str = player->getTeam();
                break;
            }
        }
        for (size_t i = 0; i <= team.size(); i++) {
            if (team_str == team[i]) {
                return messageBox.addMessage(message, user);
            }
        }
    }

    std::vector<std::string> team;

  private:
    void handleEvent();
    void handleServerMessage();
    void resize();

    Network::Handler &networkHandler;
    ServerMessageHandler serverMessageHandler;
    bool debug;
    Data::Map map;
    bool endGame;
    std::vector<std::string> endGameMessage;
    int offsetX, offsetY, newWidth, newHeight;
    MessageBox messageBox;
    InfoBox infoBox;
    TimeUnitInput timeUnitInput;

    Camera3D m_cam;
    bool m_is3D;
    bool m_isCameraFree;
    bool m_showCursor;
};

} // namespace GUI
