/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Display
*/

#include "Display.hpp"
#include <raylib.h>
#include "Skybox.hpp"

namespace GUI {

Display::Display(const std::string &machine, int port, bool &debug, int width, int height)
    : team(), networkHandler(machine, port), serverMessageHandler(debug, *this), map(Pos<int, 2>{1, 1}), endGame(false),
      endGameMessage(), m_newWindow((Raylib::RecWin){0, 0, width, height}), messageBox(),
      timeUnitInput(100, networkHandler), skybox(), m_cam(
                                              {(Vector3){15.0f, 5.0f, 15.0f},
                                               (Vector3){0.0f, 0.0f, 1.0f},
                                               (Vector3){0.0f, 1.0f, 0.0f},
                                               45.0f,
                                               CAMERA_PERSPECTIVE}
                                          ),
      m_menu(networkHandler, m_newWindow), m_settings(m_newWindow, debug)
{
    if (debug) {
        SetTraceLogLevel(LOG_ALL);
    } else {
        SetTraceLogLevel(LOG_ERROR);
    }
    SetTraceLogLevel(LOG_ALL);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(width, height, "Zappy");
    SetTargetFPS(60);
    SetWindowMinSize(1080, 450);
    SetExitKey(KEY_DELETE);
    resize();
    skybox.Load();
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
    if (IsKeyPressed(KEY_ESCAPE)) {
        if (m_menu.getInSettings())
            m_menu.setInSettings(false);
        else {
            (m_menu.getInGame())? m_menu.setInSettings(true) : m_menu.setClose(true);
        }
    }
    if (IsKeyPressed(KEY_P))
        m_settings.switchIs3D();
    if (m_settings.is3D()) {
        if (Raylib::isKeyPressed(KEY_R))
            m_cam.target = (Vector3){ 5.0f, 1.0f, 5.0f };
        if (Raylib::isKeyPressed(KEY_F))
            m_settings.switchIsCameraFree();
        if (Raylib::isKeyPressed(KEY_C)) {
            (m_settings.showCursor())? Raylib::disableCursor() : Raylib::enableCursor();
            m_settings.switchShowCursor();
        };
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (m_settings.is3D())
            map.checkCollision3D(infoBox, m_cam);
        else
            map.checkCollision(infoBox);
    }
    messageBox.handleInput();
    timeUnitInput.handleEvent();
}

void Display::displayMenu()
{
    ClearBackground(WHITE);
    m_menu.display();
}

void Display::displaySettings()
{
    ClearBackground(WHITE);
    m_settings.display();
}

void Display::displayGame()
{
    Raylib::clearBackground(BLACK);
    if (m_settings.is3D()) {
        if (m_settings.isCameraFree())
            Raylib::updateCamera(m_cam, CAMERA_FREE);
        else {
            Raylib::updateCamera(m_cam, CAMERA_PERSPECTIVE);
            m_cam.target = (Vector3){5.0f, 1.0f, 5.0f};
        }
        Raylib::beginMode3D(m_cam);
        skybox.Draw();
        map.displayTacticalView3D(infoBox);
        Raylib::endMode3D();
        infoBox.display(0, 0, 400, 300);
        messageBox.display(0, 0 + m_newWindow.height - 200, 400, 200);
        timeUnitInput.display(0 + 10, 0 + 340, 200, 30);
    } else {
        Raylib::drawRectangle(static_cast<float>(m_newWindow.x), static_cast<float>(m_newWindow.y),
            static_cast<float>(m_newWindow.width), static_cast<float>(m_newWindow.height), RAYWHITE);
        map.displayTacticalView(m_newWindow.x + 400, m_newWindow.y, m_newWindow.width + m_newWindow.x, m_newWindow.height + m_newWindow.y, infoBox);
        infoBox.display(m_newWindow.x, m_newWindow.y, 400, 300);
        messageBox.display(m_newWindow.x, m_newWindow.y + m_newWindow.height - 200, 400, 200);
        timeUnitInput.display(m_newWindow.x + 10, m_newWindow.y + 340, 200, 30);
    }
}

void Display::run()
{
    while (!m_menu.getClose() && !WindowShouldClose()) {
        if (!networkHandler.isRunning())
            m_menu.setInGame(false);
        handleServerMessage();

        handleEvent();
        BeginDrawing();
        if (m_menu.getInSettings())
            displaySettings();
        else {
            if (m_menu.getInGame())
                displayGame();
            else
                displayMenu();
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

    m_newWindow.width = screenWidth;
    m_newWindow.height = screenWidth * 9 / 16;

    if (m_newWindow.height > screenHeight) {
        m_newWindow.height = screenHeight;
        m_newWindow.width = screenHeight * 16 / 9;
    }

    m_newWindow.x = (screenWidth - m_newWindow.width) / 2;
    m_newWindow.y = (screenHeight - m_newWindow.height) / 2;
}

} // namespace GUI
