/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Display
*/

#pragma once

#include <string>
#include <raylib.h>
#include "../Network/NetworkHandler.hpp"
#include "ServerMessageHandler.hpp"

class ServerMessageHandler;

class Display {
public:
    Display(NetworkHandler& networkHandler, bool debug, int width=800, int height=450);
    ~Display();

    void run();

private:
    void handleServerMessage(std::string &message);

    NetworkHandler& networkHandler;
    ServerMessageHandler serverMessageHandler;
    bool debug;
};
