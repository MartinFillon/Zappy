/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Display
*/

#include "Display.hpp"

namespace GUI {

Display::Display(Network::Handler &networkHandler, bool debug, int width, int height)
    : team(), networkHandler(networkHandler), serverMessageHandler(debug, *this), debug(debug), map(Pos<int, 2>{1, 1}),
      endGame(false), endGameMessage(), screenWidth(width), screenHeight(height), offsetX(0), offsetY(0), newWidth(width), newHeight(height), messageBox(),
      timeUnitInput(100, networkHandler), m_cam({}), m_is3D(true), m_isCameraFree(true), m_showCursor(true), m_openWindow(MENU),
      m_menu(screenWidth, screenHeight, m_openWindow)
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
    SetWindowMinSize(800, 450);
    SetExitKey(KEY_DELETE);
    resize();

    m_cam.position = (Vector3){ 30.0f, 30.0f, 30.0f };
    m_cam.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    m_cam.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    m_cam.fovy = 45.0f;
    m_cam.projection = CAMERA_PERSPECTIVE;
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
        m_openWindow = (m_openWindow == MENU)? QUIT : MENU;
    }
    if (IsKeyPressed(KEY_P))
        m_is3D = !m_is3D;
    if (m_is3D) {
        if (Raylib::isKeyPressed(KEY_R))
            m_cam.target = (Vector3){ 0.0f, 0.0f, 0.0f };
        if (Raylib::isKeyPressed(KEY_F))
            m_isCameraFree = !m_isCameraFree;
        if (Raylib::isKeyPressed(KEY_C)) {
            (m_showCursor)? Raylib::disableCursor() : Raylib::enableCursor();
            m_showCursor = !m_showCursor;
        };
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (m_is3D)
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
    ClearBackground(BLUE);
}

void Display::displayGame()
{
    ClearBackground(BLACK);
    if (m_is3D) {
        map.displayTacticalView3D(infoBox, m_cam, m_isCameraFree);
    } else {
        DrawRectangle(offsetX, offsetY, newWidth, newHeight, RAYWHITE);
        map.displayTacticalView(offsetX + 400, offsetY, newWidth + offsetX, newHeight + offsetY, infoBox);
    }
    infoBox.display(offsetX, offsetY, 400, 300);
    messageBox.display(offsetX, offsetY + newHeight - 200, 400, 200);
    timeUnitInput.display(offsetX + 10, offsetY + 340, 200, 30);
}

void Display::run()
{
    while (m_openWindow != QUIT && !WindowShouldClose() && networkHandler.isRunning()) {
        handleServerMessage();

        handleEvent();
        BeginDrawing();
        switch (m_openWindow)
        {
        case MENU:
            displayMenu();
            break;
        case SETTINGS:
            displaySettings();
            break;
        case GAME:
            displayGame();
            break;
        default:
            break;
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
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();

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
