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
#include "UI/InfoBox.hpp"
#include "UI/MessageBox.hpp"
#include "UI/TimeUnitInput.hpp"
#include "ServerMessageHandler.hpp"
#include "define.hpp"
#include "Skybox.hpp"
#include "MusicGame.hpp"

namespace GUI {

class ServerMessageHandler;

class Display {
  public:
    Display(const std::string &machine, int port, bool &debug, int width = 1920, int height = 1080);
    ~Display();
    void run();

    void collision();
    void collision3D();
    void display2D(int start_x, int start_y, int end_x, int end_y);
    void display3D();

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
        for (auto &message : message) {
            addMessage(message, SERVER);
        }
    }

    int getTimeUnit() const
    {
        return timeUnitInput.getTimeUnit();
    }

    bool didChange3D() const
    {
        return Last3D != m_settings.is3D();
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
    bool Last3D;
    std::vector<std::string> endGameMessage;
    Raylib::RecWin m_newWindow;
    UI::MessageBox messageBox;
    UI::InfoBox infoBox;
    UI::TimeUnitInput timeUnitInput;
    Skybox skybox;
    Camera3D m_cam;
    MusicGame m_music;

    Menu m_menu;
    Settings m_settings;
};

} // namespace GUI
