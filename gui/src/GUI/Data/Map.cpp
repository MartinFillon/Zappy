/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Mapp
*/

#include "Map.hpp"
#include <cstddef>
#include <memory>
#include <raylib.h>
#include <vector>
#include "../ModelManager/Model3D.hpp"
#include "../Raylib.hpp"
#include "Inventory.hpp"

namespace GUI {
namespace Data {

Map::Map(int x, int y) : m_size({x, y}), x(0), y(0), end_x(0), end_y(0)
{
    resize(x, y);
}

Map::Map(const Pos<int, 2> &pos) : m_size(pos), x(0), y(0), end_x(0), end_y(0)
{
    resize(pos);
    std::shared_ptr<Player> test =
        std::make_shared<Player>(0, 0, static_cast<Data::Player::Direction>(1), 42, "debugTeam", 99, true);
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
        std::cout << "wanted (" << x << ", " << y << ") | me: ()" << tile.getPos().x() << ", " << tile.getPos().y()
                  << ")" << std::endl;
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

void Map::checkCollision(InfoBox &infoBox) const
{
    int mapWidth = end_x - x;
    int mapHeight = end_y - y;
    float tileSize = std::min(mapWidth / m_size.x(), mapHeight / m_size.y());

    for (auto player : m_players) {
        float playerCenterX = player->getPos().x() * tileSize + x + tileSize / 2;
        float playerCenterY = player->getPos().y() * tileSize + y + tileSize / 2;
        if (Raylib::checkCollisionMouseCircle(playerCenterX, playerCenterY, tileSize / 6)) {
            auto &item = infoBox.getItem();
            if (item == player) {
                infoBox.setPrint(!infoBox.isPrint());
            } else {
                item = player;
                infoBox.setPosTile(0.25, 0.25, 0.25);
                infoBox.setSize(0.5);
            }
            return;
        }
    }
    for (auto tile : m_map) {
        float tileX = tile->getPos().x() * tileSize + x;
        float tileY = tile->getPos().y() * tileSize + y;
        if (Raylib::checkCollisionMouseSquare(tileX, tileY, tileSize)) {
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
    Ray ray = Raylib::GetMouseRay(cam);
    RayCollision collision = {};
    RayCollision collisionTmp = {};
    InfoBox tmpInfo = infoBox;

    for (auto player : m_players) {
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
        }
    }
    for (auto tile : m_map) {
        float tileX = tile->getPos().x() * tileSize + tileSize / 2.0f;
        float tileZ = tile->getPos().y() * tileSize + tileSize / 2.0f;
        collisionTmp = Raylib::getRayCollisionCube(ray, {tileX, 0, tileZ}, tileSize);
        if (collisionTmp.hit && (!collision.hit || collisionTmp.distance < collision.distance)) {
            collision = collisionTmp;
            tmpInfo.setItem(tile);
            tmpInfo.setPosTile(0.0f, 0.0f, 0.0f);
            tmpInfo.setSize(1.0f);
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

void Map::displayTacticalView(int start_x, int start_y, int end_x, int end_y, const InfoBox &info) const
{
    this->x = start_x;
    this->y = start_y;
    this->end_x = end_x;
    this->end_y = end_y;
    int mapWidth = end_x - start_x;
    int mapHeight = end_y - start_y;
    float tileSize = std::min(mapWidth / m_size.x(), mapHeight / m_size.y());

    for (int y = 0; y < m_size.y(); y++) {
        for (int x = 0; x < m_size.x(); x++) {
            auto &ressources = getTile(x, y).getInventory();

            float tileX = x * tileSize + start_x;
            float tileY = y * tileSize + start_y;

            Raylib::drawSquare(tileX, tileY, tileSize, BROWN);
            for (int i = 0; i < 7; ++i) {
                if (ressources[i] == 0)
                    continue;
                Color color = (ressources[i] <= SIZE_STEP_1) ? RED : (ressources[i] <= SIZE_STEP_2) ? ORANGE : GREEN;
                float ressourceX = tileX + (i % 3) * tileSize / 3;
                float ressourceY = tileY + (i / 3) * tileSize / 3;
                Raylib::drawSquare(ressourceX, ressourceY, tileSize / 3, color);
            }
            Raylib::drawSquareLines(tileX, tileY, tileSize, BLACK);
        }
    }
    for (const auto &player : m_players) {
        if (!player->isHatched())
            continue;
        int playerX = player->getPos().x() * tileSize + start_x + tileSize / 2;
        int playerY = player->getPos().y() * tileSize + start_y + tileSize / 2;

        Raylib::drawCircle(playerX, playerY, tileSize / 6, Color{0, 121, 241, 150});
    }
    for (const auto &egg : m_eggs) {
        if (egg == nullptr) {
            continue;
        }
        int eggX = egg->getPosition().x() * tileSize + start_x + tileSize / 2;
        int eggY = egg->getPosition().y() * tileSize + start_y + tileSize / 2;

        Raylib::drawCircle(eggX, eggY, tileSize / 8, Color{253, 249, 0, 150});
    }
    if (info.isPrint() && info.getItem() != nullptr) {
        auto item = info.getItem();
        float itemX = (item->getPos().x() + info.getPosTile().x()) * tileSize + start_x;
        float itemZ = (item->getPos().y() + info.getPosTile().y()) * tileSize + start_y;
        Raylib::drawSquareLines(itemX, itemZ, tileSize * info.getSize(), GREEN);
    }
}

void Map::displayTacticalView3D(const InfoBox &info, Camera3D &cam) const
{
    float tileSize = 1.0f;

    Raylib::clearBackground(RAYWHITE);
    Raylib::beginMode3D(cam);
    if (qm.getSize() == 0) {
        qm.init();
    }

    for (auto tile : m_map)
    {
        float tileX = tile->getPos().x() * tileSize + tileSize / 2;
        float tileZ = tile->getPos().y() * tileSize + tileSize / 2;
        qm.DrawGrass({tileX, 0.5, tileZ});
        Raylib::drawCubeWires({tileX, 0, tileZ}, tileSize, BROWN);
        Inventory inv = tile->getInventory();
        for (size_t i = 0; i < inv.inv.size(); i++) {
            if (inv.inv[i] == 0) {
                continue;
            }
            int size = (inv.inv[i] <= SIZE_STEP_1) ? 0 : (inv.inv[i] <= SIZE_STEP_2) ? 1 : 2;
            qm.Draw(size, i, tileX, tileZ);
        }
    }

    for (const auto &egg : m_eggs) {
        if (egg == nullptr)
            continue;
        float eggX = egg->getPosition().x() * tileSize + tileSize / 2;
        float eggZ = egg->getPosition().y() * tileSize + tileSize / 2;
        Raylib::drawSphere({eggX, tileSize / 8 + tileSize / 2, eggZ}, tileSize / 8, Color{253, 249, 0, 255});
    }

    for (const auto &player : m_players) {
         if (!player || !player->isHatched())
            continue;
        float playerX = player->getPos().x() * tileSize + tileSize / 2;
        float playerZ = player->getPos().y() * tileSize + tileSize / 2;
        Raylib::drawSphere({playerX, tileSize / 6 + tileSize / 2, playerZ}, tileSize / 6, Color{0, 121, 241, 255});
    }

    if (info.isPrint() && info.getItem() != nullptr) {
        auto item = info.getItem();
        float itemX = (item->getPos().x() + info.getPosTile().x()) * tileSize + tileSize / 2;
        float itemY = info.getPosTile().y() * tileSize;
        float itemZ = (item->getPos().y() + info.getPosTile().z()) * tileSize + tileSize / 2;
        float plus = tileSize / 10.0f;
        float sizeCube = tileSize * info.getSize() + 2 * plus;
        Raylib::drawCubeWires({itemX, itemY, itemZ}, sizeCube, GREEN);
    }

    Raylib::endMode3D();
}

} // namespace Data
} // namespace GUI
