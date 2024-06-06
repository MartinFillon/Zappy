/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Mapp
*/

#include "Map.hpp"
#include <raylib.h>

namespace GUI {
namespace Data {

Map::Map(int x, int y) : m_size({x, y})
{
    resize(x, y);
}

Map::Map(const Pos<int, 2> &pos) : m_size(pos)
{
    resize(pos);
    std::shared_ptr<Player> test = std::make_shared<Player>(0, 0, static_cast<Data::Player::Direction>(1), 42, "newTeam", 99, false);
    m_players.push_back(test);
}

Tile &Map::getTile(const Pos<int, 2> &pos)
{
    if (pos.x() >= m_size.x() || pos.y() >= m_size.y()) {
        throw std::out_of_range("Position out of map bounds");
    }
    return *m_map.at(pos.y() * m_size.x() + pos.x());
}

Tile &Map::getTile(int x, int y)
{
    if (x >= m_size.x() || y >= m_size.y()) {
        throw std::out_of_range("Position out of map bounds");
    }
    return *m_map.at(y * m_size.x() + x);
}

Tile Map::getTile(const Pos<int, 2> &pos) const
{
    if (pos.x() >= m_size.x() || pos.y() >= m_size.y()) {
        throw std::out_of_range("Position out of map bounds");
    }
    return *m_map.at(pos.y() * m_size.x() + pos.x());
}

Tile Map::getTile(int x, int y) const
{
    if (x >= m_size.x() || y >= m_size.y()) {
        throw std::out_of_range("Position out of map bounds");
    }
    Tile tile = *m_map.at(y * m_size.x() + x);
    if (x != tile.getPos().x() && y != tile.getPos().y())
        std::cout << "wanted (" << x << ", " << y << ") | me: ()" << tile.getPos().x() << ", " << tile.getPos().y() << ")" << std::endl;
    return tile;
}

std::vector<std::shared_ptr<Player>> &Map::getPlayers()
{
    return m_players;
}

std::vector<std::shared_ptr<Egg>> &Map::getEggs()
{
    return m_eggs;
}

Pos<int, 2> Map::getSize() const
{
    return m_size;
}

void Map::resize(int x, int y)
{
    int size_map = static_cast<int>(m_map.size());

    if (size_map > x * y || size_map < x * y) {
        m_map.clear();
        for (int y = 0; y < x; y++) {
            for (int i = 0; i < x; i++) {
                m_map.push_back(std::make_shared<Tile>(i, y));
            }
        }
        m_size = {x, y};
    }
}

void Map::resize(const Pos<int, 2> &size)
{
    int size_map = static_cast<int>(m_map.size());
    int x = size.x();
    int y = size.y();

    if (size_map > x * y || size_map < x * y) {
        m_map.clear();
        for (int y = 0; y < x; y++) {
            for (int i = 0; i < x; i++) {
                m_map.push_back(std::make_shared<Tile>(i, y));
            }
        }
        m_size = {x, y};
    }
}

void Map::checkCollision(int start_x, int start_y, int end_x, int end_y, InfoBox &infoBox) const
{
    int mapWidth = end_x - start_x;
    int mapHeight = end_y - start_y;
    float tileSize = std::min(mapWidth / m_size.x(), mapHeight / m_size.y());

    for (auto player : m_players) {
        float playerCenterX = player->getPos().x() * tileSize + start_x + tileSize / 2;
        float playerCenterZ = player->getPos().y() * tileSize + start_y + tileSize / 2;
        if (CheckCollisionPointCircle(GetMousePosition(), {playerCenterX, playerCenterZ}, tileSize / 6)) {
            auto &item = infoBox.getItem();
            if (item == player) {
                infoBox.setPrint(!infoBox.isPrint());
            } else {
                item = player;
                infoBox.setPosTile(0.25, 0.25, 0.25);
                infoBox.setSize(0.4);
            }
            return;
        }
    }
    for (auto tile : m_map) {
        float tileX = tile->getPos().x() * tileSize + start_x;
        float tileZ = tile->getPos().y() * tileSize + start_y;
        if (CheckCollisionPointRec(GetMousePosition(), {tileX, tileZ, tileSize, tileSize})) {
            auto &item = infoBox.getItem();
            if (item == tile) {
                infoBox.setPrint(!infoBox.isPrint());
            } else {
                item = tile;
                infoBox.setPosTile(0, 0, 0);
                infoBox.setSize(1);
            }
        }
    }
}

void Map::checkCollision3D(InfoBox &infoBox, const Camera3D &cam) const
{
    float tileSize = 1.0f;
    Ray ray = GetMouseRay(GetMousePosition(), cam);
    RayCollision collision = {};
    RayCollision collisionTmp = {};
    std::shared_ptr<ISelectItem> tmpItemSelect = nullptr;
    Pos<float, 3> tmpPos = {0.0f, 0.0f, 0.0f};
    float tmpSize = 0.0f;

    for (auto player : m_players) {
        float playerCenterX = player->getPos().x() * tileSize + tileSize / 2.0f;
        float playerCenterZ = player->getPos().y() * tileSize + tileSize / 2.0f;
        collisionTmp = GetRayCollisionSphere(ray,
            (Vector3){playerCenterX, tileSize / 6.0f + tileSize / 2.0f, playerCenterZ},
            tileSize / 6.0f);
        if (collisionTmp.hit && (!collision.hit || collisionTmp.distance < collision.distance)) {
            collision = collisionTmp;
            tmpItemSelect = player;
            tmpPos = {0.0f, 0.67f, 0.0f};
            tmpSize = 0.4f;
        }
    }
    for (auto tile : m_map) {
        float tileX = tile->getPos().x() * tileSize + tileSize / 2.0f;
        float tileZ = tile->getPos().y() * tileSize + tileSize / 2.0f;
        collisionTmp = GetRayCollisionBox(ray, (BoundingBox){
            (Vector3){tileX - tileSize / 2.0f, - tileSize / 2.0f, tileZ - tileSize / 2.0f},
            (Vector3){tileX + tileSize / 2.0f, tileSize / 2.0f, tileZ + tileSize / 2.0f}});
        if (collisionTmp.hit && (!collision.hit || collisionTmp.distance < collision.distance)) {
            collision = collisionTmp;
            tmpItemSelect = tile;
            tmpPos = {0.0f, 0.0f, 0.0f};
            tmpSize = 1.0f;
        }
    }
    if (tmpItemSelect != nullptr) {
        auto &item = infoBox.getItem();
        if (item == tmpItemSelect) {
            infoBox.setPrint(!infoBox.isPrint());
            return;
        }
        item = tmpItemSelect;
        infoBox.setPosTile(tmpPos);
        infoBox.setSize(tmpSize);
        infoBox.setPrint(true);
    }
}

void Map::displayTacticalView(int start_x, int start_y, int end_x, int end_y, const InfoBox &info) const
{
    int mapWidth = end_x - start_x;
    int mapHeight = end_y - start_y;
    float tileSize = std::min(mapWidth / m_size.x(), mapHeight / m_size.y());

    for (int y = 0; y < m_size.y(); y++) {
        for (int x = 0; x < m_size.x(); x++) {
            auto &ressources = getTile(x, y).getInventory();

            float tileX = x * tileSize + start_x;
            float tileZ = y * tileSize + start_y;

            for (int i = 0; i < 7; i++) {
                float ressourceX = tileX + (i % 3) * tileSize / 3;
                float ressourceY = tileZ + (i / 3) * tileSize / 3;

                if (ressources[i] > 0 && ressources[i] < 2) {
                    DrawRectangle(ressourceX, ressourceY, tileSize / 3, tileSize / 3, ORANGE);
                } else if (ressources[i] >= 2) {
                    DrawRectangle(ressourceX, ressourceY, tileSize / 3, tileSize / 3, GREEN);
                } else {
                    DrawRectangle(ressourceX, ressourceY, tileSize / 3, tileSize / 3, RED);
                }
            }
            DrawRectangleLines(tileX, tileZ, tileSize, tileSize, BLACK);
        }
    }
    for (const auto &player : m_players) {
        int playerX = player->getPos().x() * tileSize + start_x + tileSize / 2;
        int playerZ = player->getPos().y() * tileSize + start_y + tileSize / 2;

        DrawCircle(playerX, playerZ, tileSize / 6, Color{0, 121, 241, 150});
    }
    for (const auto &egg : m_eggs) {
        int eggX = egg->getPosition().x() * tileSize + start_x + tileSize / 2;
        int eggZ = egg->getPosition().y() * tileSize + start_y + tileSize / 2;

        DrawCircle(eggX, eggZ, tileSize / 8, Color{253, 249, 0, 150});
    }
    if (info.isPrint() && info.getItem() != nullptr) {
        auto item = info.getItem();
        float itemX = (item->getPos().x() + info.getPosTile().x()) * tileSize + start_x;
        float itemZ = (item->getPos().y() + info.getPosTile().y()) * tileSize + start_y;
        DrawRectangleLines(itemX, itemZ, tileSize * info.getSize(), tileSize * info.getSize(), GREEN);
    }
}

void Map::displayTacticalView3D(const InfoBox &info, Camera3D &cam, bool &showCursor, bool &isCameraFree) const
{
    float tileSize = 1.0f;


    if (IsKeyPressed('R')) cam.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    if (IsKeyPressed('F')) isCameraFree = !isCameraFree;
    if (IsKeyPressed('C')) {
        if (showCursor) DisableCursor();
        else EnableCursor();
        showCursor = !showCursor;
    };
    if (isCameraFree) UpdateCamera(&cam, CAMERA_FREE);

    ClearBackground(RAYWHITE);
    BeginMode3D(cam);

    DrawGrid(100, 1.0f);
    for (auto tile : m_map) {
        float tileX = tile->getPos().x() * tileSize + tileSize / 2;
        float tileZ = tile->getPos().y() * tileSize + tileSize / 2;
        DrawCube({tileX, 0, tileZ}, tileSize, tileSize, tileSize, RED);
        DrawCubeWires({tileX, 0, tileZ}, tileSize, tileSize, tileSize, BROWN);
    }
    for (const auto &player : m_players) {
        float playerX = player->getPos().x() * tileSize + tileSize / 2;
        float playerZ = player->getPos().y() * tileSize + tileSize / 2;

        DrawSphere({playerX, tileSize / 6 + tileSize / 2 ,playerZ}, tileSize / 6, Color{0, 121, 241, 150});
    }
    for (const auto &egg : m_eggs) {
        float eggX = egg->getPosition().x() * tileSize + tileSize / 2;
        float eggZ = egg->getPosition().y() * tileSize + tileSize / 2;

        DrawSphere({eggX, tileSize / 8 + tileSize / 2, eggZ}, tileSize / 8, Color{253, 249, 0, 150});
    }
    if (info.isPrint() && info.getItem() != nullptr) {
        auto item = info.getItem();
        float itemX = (item->getPos().x() + info.getPosTile().x()) * tileSize + tileSize / 2;
        float itemY = info.getPosTile().y() * tileSize;
        float itemZ = (item->getPos().y() + info.getPosTile().z()) * tileSize + tileSize / 2;
        float plus = tileSize / 10.0f;
        float sizeCube = tileSize * info.getSize() + 2 * plus;
        DrawCubeWires({itemX, itemY, itemZ}, sizeCube, sizeCube, sizeCube, GREEN);
    }
    EndMode3D();
}

} // namespace Data
} // namespace GUI