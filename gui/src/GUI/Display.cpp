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
    : team(), networkHandler(machine, port), serverMessageHandler(debug, *this), map(Pos<int, 2>{1, 1}), endGame(false), Last3D(true),
      endGameMessage(), m_newWindow((Raylib::RecWin){0, 0, width, height}), messageBox(),
      timeUnitInput(100, networkHandler), skybox(), m_cam(
                                              {(Vector3){15.0f, 5.0f, 15.0f},
                                               (Vector3){0.0f, 0.0f, 1.0f},
                                               (Vector3){0.0f, 1.0f, 0.0f},
                                               45.0f,
                                               CAMERA_PERSPECTIVE}
                                          ),
      m_menu(networkHandler, m_newWindow, m_music), m_settings(m_newWindow, m_music, debug)
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
    SetExitKey(KEY_DELETE);
    resize();
    skybox.Load();
    m_music.load();
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
        m_music.playSound();
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
    if (!m_menu.getInGame()) {
        if (!m_menu.getInSettings())
            m_menu.eventhandler();
        else
            m_settings.eventhandler();
    }
    if (endGame && Raylib::isKeyPressed(KEY_SPACE)) {
        endGame = false;
        m_menu.setInGame(false);
    }
    messageBox.handleInput();
    timeUnitInput.handleEvent();
    if (didChange3D()) {
        resize();
    }
    Last3D = m_settings.is3D();
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

void Display::displayEndGame()
{
    int fontSize = HeightToFontSize(m_newWindow.height);
    std::string title = "THE WINNER IS";
    std::string comment = "PRESS SPACE TO RETURN TO THE MENU";
    Vector2 sizeTitle = Raylib::getMeasureTextEx(title, fontSize / 2);
    int sizeComment = Raylib::getMeasureTextEx(comment, fontSize / 4).x;

    ClearBackground(BLACK);
    Raylib::drawText(comment,
        m_newWindow.x + (m_newWindow.width - sizeComment) / 2.0f,
        m_newWindow.y + m_newWindow.height * MulCommentY,
        fontSize / 4, GRAY);
    Raylib::drawText(title,
        m_newWindow.x + (m_newWindow.width - sizeTitle.x) / 2.0f,
        m_newWindow.y + m_newWindow.height * MulEndY - sizeTitle.y,
        fontSize / 2, PURPLE);
    endGameMessage.push_back("Blloooop :3");
    if (endGameMessage.empty())
        return;
    const std::string &str = endGameMessage.at(0);
    int sizeText = Raylib::getMeasureTextEx(str, fontSize).x;
    Raylib::drawText(str,
        m_newWindow.x + (m_newWindow.width - sizeText) / 2.0f,
        m_newWindow.y + m_newWindow.height * MulEndY,
        fontSize, PURPLE);
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
    } else {
        Raylib::drawRectangle(static_cast<float>(m_newWindow.x), static_cast<float>(m_newWindow.y),
            static_cast<float>(m_newWindow.width), static_cast<float>(m_newWindow.height), RAYWHITE);
        map.displayTacticalView(m_newWindow.x + 400, m_newWindow.y, m_newWindow.width + m_newWindow.x, m_newWindow.height + m_newWindow.y, infoBox);
    }
    infoBox.display();
    messageBox.display();
    timeUnitInput.display();
}

void Display::run()
{
    while (!m_menu.getClose() && !WindowShouldClose()) {
        m_music.updateMusic();
        if (!networkHandler.isRunning())
            m_menu.setInGame(false);
        handleServerMessage();

        handleEvent();
        BeginDrawing();
        if (endGame) {
            displayEndGame();
            EndDrawing();
            continue;
        }
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

    if (m_settings.is3D()) {
        messageBox.resize(0, screenHeight - 200, 400, 200);
        infoBox.resize(0, 0, 400, 300);
        timeUnitInput.resize(0 + 10, 0 + 340, 200, 30);
    } else {
        messageBox.resize(m_newWindow.x, m_newWindow.y + m_newWindow.height - 200, 400, 200);
        infoBox.resize(m_newWindow.x, m_newWindow.y, 400, 300);
        timeUnitInput.resize(m_newWindow.x + 10, m_newWindow.y + 340, 200, 30);
    }
}

} // namespace GUI
