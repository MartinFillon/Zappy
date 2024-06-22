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
#include "Menu/Menu.hpp"
#include "Menu/Settings.hpp"
#include "Data/Map.hpp"
#include "MessageBox.hpp"
#include "TimeUnitInput.hpp"
#include "ServerMessageHandler.hpp"
#include "define.hpp"
#include "Skybox.hpp"

namespace GUI {

class ServerMessageHandler;

class Display {
  public:
    Display(const std::string &machine, int port, bool &debug, int width = 1920, int height = 1080);
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
    void displayMenu();
    void displaySettings();
    void displayGame();
    void handleEvent();
    void handleServerMessage();
    void resize();

    Network::Handler networkHandler;
    ServerMessageHandler serverMessageHandler;

    Data::Map map;

    bool endGame;
    std::vector<std::string> endGameMessage;

    Raylib::RecWin m_newWindow;
    MessageBox messageBox;
    InfoBox infoBox;
    TimeUnitInput timeUnitInput;
    Skybox skybox;

    Camera3D m_cam;

    Menu m_menu;
    Settings m_settings;
};

} // namespace GUI
