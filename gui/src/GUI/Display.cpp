/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Display
*/

#include "Display.hpp"
#include <raylib.h>
#include "Data/Map.hpp"
#include "ServerMessageHandler.hpp"

namespace GUI {

Display::Display(Network::Handler &networkHandler, bool debug, int width, int height)
    : networkHandler(networkHandler), serverMessageHandler(debug, *this), debug(debug), map(Pos<int, 2>{1, 1}), timeUnit(100), endGame(false), endGameMessage() {
    if (debug) {
        SetTraceLogLevel(LOG_ALL);
    } else {
        SetTraceLogLevel(LOG_ERROR);
    }
    InitWindow(width, height, "Zappy");
}

Display::~Display() {
    CloseWindow();
}

void Display::run() {
    std::string message;

    while (!WindowShouldClose()) {
        handleServerMessage(message);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText(message.c_str(), 190, 250, 20, BLACK);
        EndDrawing();
    }
}

void Display::handleServerMessage(std::string &message) {
    if (!networkHandler.getMessage(message)) {
        return;
    }
    serverMessageHandler.handleServerMessage(message);
}

} // namespace GUI
