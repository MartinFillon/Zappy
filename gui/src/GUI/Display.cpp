/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Display
*/

#include "Display.hpp"
#include <raylib.h>
#include <vector>
#include "Data/Player.hpp"
#include "Skybox.hpp"

namespace GUI {

Display::Display(const std::string &machine, int port, bool &debug, int width, int height)
    : team(), networkHandler(machine, port), serverMessageHandler(debug, *this), map(Pos<int, 2>{1, 1}), endGame(false),
      Last3D(true), endGameMessage(), m_newWindow((Raylib::RecWin){0, 0, width, height}), messageBox(),
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
            (m_menu.getInGame()) ? m_menu.setInSettings(true) : m_menu.setClose(true);
        }
    }
    if (IsKeyPressed(KEY_P))
        m_settings.switchIs3D();
    if (m_settings.is3D()) {
        if (Raylib::isKeyPressed(KEY_R))
            m_cam.target = (Vector3){5.0f, 1.0f, 5.0f};
        if (Raylib::isKeyPressed(KEY_F))
            m_settings.switchIsCameraFree();
        if (Raylib::isKeyPressed(KEY_C)) {
            (m_settings.showCursor()) ? Raylib::disableCursor() : Raylib::enableCursor();
            m_settings.switchShowCursor();
        };
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (m_settings.is3D())
            collision3D();
        else
            collision();
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
    if (endGameMessage.empty())
        endGameMessage.push_back("Unknow");
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
        display3D();
        Raylib::endMode3D();
    } else {
        Raylib::drawRectangle(
            static_cast<float>(m_newWindow.x),
            static_cast<float>(m_newWindow.y),
            static_cast<float>(m_newWindow.width),
            static_cast<float>(m_newWindow.height),
            RAYWHITE
        );
        display2D(
            m_newWindow.x + 400, m_newWindow.y, m_newWindow.width + m_newWindow.x, m_newWindow.height + m_newWindow.y
        );
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

void Display::collision()
{
    std::vector<std::shared_ptr<Data::Player>> players = map.getPlayers();
    std::vector<std::shared_ptr<Data::Tile>> tiles = map.getTiles();
    int mapWidth = map.end_x - map.x;
    int mapHeight = map.end_y - map.y;
    float tileSize = std::min(mapWidth / map.getSize().x(), mapHeight / map.getSize().y());

    for (auto player : players) {
        float playerCenterX = player->getPos().x() * tileSize + map.x + tileSize / 2;
        float playerCenterY = player->getPos().y() * tileSize + map.y + tileSize / 2;
        if (Raylib::checkCollisionMouseCircle(playerCenterX, playerCenterY, tileSize / 6)) {
            auto &item = infoBox.getItem();
            if (item == player) {
                infoBox.setPrint(!infoBox.isPrint());
            } else {
                item = player;
                infoBox.setPosTile(0.25, 0.25, 0.25);
                infoBox.setSize(0.5);
                networkHandler.requestPlayerInventory(player->getId());
                networkHandler.requestPlayerLevel(player->getId());
            }
            return;
        }
    }
    for (auto tile : tiles) {
        float tileX = tile->getPos().x() * tileSize + map.x;
        float tileY = tile->getPos().y() * tileSize + map.y;
        if (Raylib::checkCollisionMouseSquare(tileX, tileY, tileSize)) {
            auto &item = infoBox.getItem();
            if (item == tile) {
                infoBox.setPrint(!infoBox.isPrint());
            } else {
                item = tile;
                infoBox.setPosTile(0, 0, 0);
                infoBox.setSize(1);
                networkHandler.requestTileContent(tile->getPos().x(), tile->getPos().y());
            }
        }
    }
}

void Display::collision3D()
{
    float tileSize = 1.0f;
    Ray ray = Raylib::GetMouseRay(m_cam);
    RayCollision collision = {};
    RayCollision collisionTmp = {};
    UI::InfoBox tmpInfo = infoBox;
    std::vector<std::shared_ptr<Data::Player>> players = map.getPlayers();
    std::vector<std::shared_ptr<Data::Tile>> tiles = map.getTiles();

    for (auto player : players) {
        float playerCenterX = player->getPos().x() * tileSize + tileSize / 2.0f;
        float playerCenterZ = player->getPos().y() * tileSize + tileSize / 2.0f;
        collisionTmp = Raylib::getRayCollisionSphere(
            ray, (Vector3){playerCenterX, tileSize / 6.0f + tileSize / 2.0f, playerCenterZ}, tileSize / 6.0f
        );
        if (collisionTmp.hit && (!collision.hit || collisionTmp.distance < collision.distance)) {
            collision = collisionTmp;
            tmpInfo.setItem(player);
            tmpInfo.setPosTile(0.0f, 0.67f, 0.0f);
            tmpInfo.setSize(0.4f);
            networkHandler.requestPlayerInventory(player->getId());
            networkHandler.requestPlayerLevel(player->getId());
        }
    }
    for (auto tile : tiles) {
        float tileX = tile->getPos().x() * tileSize + tileSize / 2.0f;
        float tileZ = tile->getPos().y() * tileSize + tileSize / 2.0f;
        collisionTmp = Raylib::getRayCollisionCube(ray, {tileX, 0, tileZ}, tileSize);
        if (collisionTmp.hit && (!collision.hit || collisionTmp.distance < collision.distance)) {
            collision = collisionTmp;
            tmpInfo.setItem(tile);
            tmpInfo.setPosTile(0.0f, 0.0f, 0.0f);
            tmpInfo.setSize(1.0f);
            networkHandler.requestTileContent(tile->getPos().x(), tile->getPos().y());
        }
    }
    auto &tmpItem = tmpInfo.getItem();
    if (tmpItem != nullptr) {
        auto &item = infoBox.getItem();
        if (item == tmpItem) {
            infoBox.setPrint(!infoBox.isPrint());
            return;
        }
        infoBox = tmpInfo;
        infoBox.setPrint(true);
    }
}

void Display::display2D(int start_x, int start_y, int end_x, int end_y)
{
    map.set2DDisplay(start_x, start_y, end_x, end_y);
    int mapWidth = end_x - start_x;
    int mapHeight = end_y - start_y;
    float tileSize = std::min(mapWidth / map.getSize().x(), mapHeight / map.getSize().y());
    std::vector<std::shared_ptr<Data::Tile>> tiles = map.getTiles();

    for (int y = 0; y < map.getSize().y(); y++) {
        for (int x = 0; x < map.getSize().x(); x++) {
            auto &ressources = map.getTile(x, y).getInventory();

            float tileX = x * tileSize + start_x;
            float tileY = y * tileSize + start_y;

            Raylib::drawSquare(tileX, tileY, tileSize, BROWN);
            for (int i = 0; i < 7; ++i) {
                if (ressources[i] == 0)
                    continue;
                Color color = (ressources[i] <= SIZE_STEP_1) ? RED : (ressources[i] <= SIZE_STEP_2) ? ORANGE : GREEN;
                float ressourceX = tileX + (i % 3) * (tileSize / 3.0f);
                float ressourceY = tileY + (i / 3) * (tileSize / 3.0f);
                Raylib::drawSquare(ressourceX, ressourceY, tileSize / 3.0f, color);
            }
            Raylib::drawSquareLines(tileX, tileY, tileSize, BLACK);
        }
    }
    for (const auto &player : map.getPlayers()) {
        if (!player->isHatched())
            continue;
        int playerX = player->getPos().x() * tileSize + start_x + tileSize / 2;
        int playerY = player->getPos().y() * tileSize + start_y + tileSize / 2;

        Raylib::drawCircle(playerX, playerY, tileSize / 6, Color{0, 121, 241, 200});
    }
    for (const auto &egg : map.getEggs()) {
        if (egg == nullptr) {
            continue;
        }
        int eggX = egg->getPosition().x() * tileSize + start_x + tileSize / 2;
        int eggY = egg->getPosition().y() * tileSize + start_y + tileSize / 2;

        Raylib::drawCircle(eggX, eggY, tileSize / 8, Color{253, 249, 0, 200});
    }
    if (infoBox.isPrint() && infoBox.getItem() != nullptr) {
        auto item = infoBox.getItem();
        float itemX = (item->getPos().x() + infoBox.getPosTile().x()) * tileSize + start_x;
        float itemZ = (item->getPos().y() + infoBox.getPosTile().y()) * tileSize + start_y;
        Raylib::drawSquareLines(itemX, itemZ, tileSize * infoBox.getSize(), GREEN);
    }
}

void Display::display3D()
{
    float tileSize = 1.0f;

    if (map.qm.getSize() == 0) {
        map.qm.init();
    }

    for (auto tile : map.getTiles()) {
        float tileX = tile->getPos().x() * tileSize + tileSize / 2;
        float tileZ = tile->getPos().y() * tileSize + tileSize / 2;
        map.qm.DrawGrass({tileX, 0.5, tileZ});
        Raylib::drawCubeWires({tileX, 0.02, tileZ}, tileSize, (Color){100, 100, 100, 150});
        Data::Inventory inv = tile->getInventory();
        for (size_t i = 0; i < inv.inv.size(); i++) {
            if (inv.inv[i] == 0) {
                continue;
            }
            int size = (inv.inv[i] <= SIZE_STEP_1) ? 0 : (inv.inv[i] <= SIZE_STEP_2) ? 1 : 2;
            map.qm.Draw(size, i, tileX, tileZ);
        }
    }

    for (const auto &egg : map.getEggs()) {
        if (egg == nullptr)
            continue;
        float eggX = egg->getPosition().x() * tileSize + tileSize / 2;
        float eggZ = egg->getPosition().y() * tileSize + tileSize / 2;
        map.qm.DrawEgg({eggX, tileSize / 2, eggZ});
    }

    for (const auto &player : map.getPlayers()) {
        if (!player || !player->isHatched())
            continue;
        float playerX = player->getPos().x() * tileSize + tileSize / 2;
        float playerZ = player->getPos().y() * tileSize + tileSize / 2;
        map.qm.DrawPlayer({playerX, tileSize / 2, playerZ}, player->getOrientation());
    }

    if (infoBox.isPrint() && infoBox.getItem() != nullptr) {
        auto item = infoBox.getItem();
        float itemX = (item->getPos().x() + infoBox.getPosTile().x()) * tileSize + tileSize / 2;
        float itemY = infoBox.getPosTile().y() * tileSize;
        float itemZ = (item->getPos().y() + infoBox.getPosTile().z()) * tileSize + tileSize / 2;
        float plus = tileSize / 10.0f;
        float sizeCube = tileSize * infoBox.getSize() + 2 * plus;
        Raylib::drawCubeWires({itemX, itemY, itemZ}, sizeCube, GREEN);
    }
}

} // namespace GUI
