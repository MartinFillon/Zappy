/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Display
*/

#include "Display.hpp"
#include <raylib.h>

namespace GUI {

Display::Display(Network::Handler &networkHandler, bool debug, int width, int height)
    : team(), networkHandler(networkHandler), serverMessageHandler(debug, *this), debug(debug), map(Pos<int, 2>{1, 1}),
      endGame(false), endGameMessage(), offsetX(0), offsetY(0), newWidth(width), newHeight(height), messageBox(),
      timeUnitInput(100, networkHandler), m_cam(
                                              {(Vector3){15.0f, 5.0f, 15.0f},
                                               (Vector3){0.0f, 0.0f, 1.0f},
                                               (Vector3){0.0f, 1.0f, 0.0f},
                                               45.0f,
                                               CAMERA_PERSPECTIVE}
                                          ),
      m_is3D(true), m_isCameraFree(true), m_showCursor(false)
{
    if (debug) {
        SetTraceLogLevel(LOG_ALL);
    } else {
        SetTraceLogLevel(LOG_ERROR);
    }
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(width, height, "Zappy");
    SetTargetFPS(60);
    SetWindowMinSize(1080, 450);
    resize();
}

Display::~Display()
{
    CloseWindow();
    networkHandler.stop();
}

void Display::handleEvent()
{
    if (IsWindowResized()) {
        resize();
    }
    if (IsKeyPressed('P'))
        m_is3D = !m_is3D;
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (m_is3D)
            map.checkCollision3D(infoBox, m_cam);
        else
            map.checkCollision(infoBox);
    }
    messageBox.handleInput();
    timeUnitInput.handleEvent();
}

void Display::run()
{
    while (!WindowShouldClose() && networkHandler.isRunning()) {
        handleServerMessage();

        handleEvent();
        BeginDrawing();
        ClearBackground(BLACK);
        if (m_is3D) {
            map.displayTacticalView3D(infoBox, m_cam, m_isCameraFree, m_showCursor);
            infoBox.display(0, 0, 400, 300);
            messageBox.display(0, 0 + newHeight - 200, 400, 200);
            timeUnitInput.display(0 + 10, 0 + 340, 200, 30);
        } else {
            DrawRectangle(offsetX, offsetY, newWidth, newHeight, RAYWHITE);
            map.displayTacticalView(offsetX + 400, offsetY, newWidth + offsetX, newHeight + offsetY, infoBox);
            infoBox.display(offsetX, offsetY, 400, 300);
            messageBox.display(offsetX, offsetY + newHeight - 200, 400, 200);
            timeUnitInput.display(offsetX + 10, offsetY + 340, 200, 30);
        }
        EndDrawing();
    }
}

void Display::handleServerMessage()
{
    std::string message;
    while (networkHandler.getMessage(message)) {
        serverMessageHandler.handleServerMessage(message);
    }
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
