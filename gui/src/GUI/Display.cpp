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
    : team(), networkHandler(networkHandler), serverMessageHandler(debug, *this), debug(debug), map(Pos<int, 2>{1, 1}),
      timeUnit(100), endGame(false), endGameMessage(), messages(), offsetX(0), offsetY(0), newWidth(width), newHeight(height)
{
    if (debug) {
        SetTraceLogLevel(LOG_ALL);
    } else {
        SetTraceLogLevel(LOG_ERROR);
    }
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(width, height, "Zappy");
    SetTargetFPS(60);
    SetWindowMinSize(800, 450);

    // Initial resize calculation
    resize();
}

Display::~Display()
{
    CloseWindow();
}

void Display::run()
{
    std::string message;

    while (!WindowShouldClose()) {
        handleServerMessage(message);

        if (IsWindowResized()) {
            resize();
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangle(offsetX, offsetY, newWidth, newHeight, RAYWHITE);
        map.displayTacticalView(offsetX, offsetY, newWidth + offsetX, newHeight + offsetY);
        EndDrawing();
    }
}

void Display::handleServerMessage(std::string &message)
{
    if (!networkHandler.getMessage(message)) {
        return;
    }
    serverMessageHandler.handleServerMessage(message);
}

void Display::resize()
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    newWidth = screenWidth;
    newHeight = screenWidth * 9 / 16;

    if (newHeight > screenHeight) {
        newHeight = screenHeight;
        newWidth = screenHeight * 16 / 9;
    }

    offsetX = (screenWidth - newWidth) / 2;
    offsetY = (screenHeight - newHeight) / 2;
}

} // namespace GUI