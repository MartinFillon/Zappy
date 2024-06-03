/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Display
*/

#include <raylib.h>

#include "Data/Map.hpp"
#include "Display.hpp"
#include "MessageBox.hpp"
#include "ServerMessageHandler.hpp"

namespace GUI {

Display::Display(Network::Handler &networkHandler, bool debug, int width, int height)
    : team(), networkHandler(networkHandler), serverMessageHandler(debug, *this), debug(debug), map(Pos<int, 2>{1, 1}),
      timeUnit(100), endGame(false), endGameMessage(), offsetX(0), offsetY(0), newWidth(width), newHeight(height),
      messageBox()
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
    resize();
}

Display::~Display()
{
    CloseWindow();
}

void Display::handleEvent()
{
    if (IsWindowResized()) {
        resize();
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        map.checkCollision(offsetX + 400, offsetY, newWidth + offsetX, newHeight + offsetY, infoBox);
    }
    messageBox.handleInput(offsetX, offsetY + newHeight - 200, 400, 200);
}

void Display::run()
{
    std::string message;

    while (!WindowShouldClose()) {
        handleServerMessage(message);

        handleEvent();
        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangle(offsetX, offsetY, newWidth, newHeight, RAYWHITE);
        map.displayTacticalView(offsetX + 400, offsetY, newWidth + offsetX, newHeight + offsetY, infoBox);
        infoBox.display(offsetX, offsetY, 400, 300);
        messageBox.display(offsetX, offsetY + newHeight - 200, 400, 200);
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
