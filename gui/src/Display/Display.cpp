/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Display
*/

#include "Display.hpp"
#include "ServerMessageHandler.hpp"

Display::Display(NetworkHandler& networkHandler, bool debug, int width, int height)
    : networkHandler(networkHandler), serverMessageHandler(debug, *this), debug(debug) {
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
    if (!networkHandler.getMessage(message))
        return;

    serverMessageHandler.handleServerMessage(message);
}
