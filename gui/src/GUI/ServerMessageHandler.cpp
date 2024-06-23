/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ServerMessageHandler
*/

#include "ServerMessageHandler.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include "Data/Player.hpp"
#include "Display.hpp"

namespace GUI {

ServerMessageHandler::ServerMessageHandler(const bool &debug, Display &display) : debug(debug), display(display)
{
    commandHandlers["msz"] = std::bind(&ServerMessageHandler::handleMapSize, this, std::placeholders::_1);
    commandHandlers["bct"] = std::bind(&ServerMessageHandler::handleTileContent, this, std::placeholders::_1);
    commandHandlers["tna"] = std::bind(&ServerMessageHandler::handleTeamNames, this, std::placeholders::_1);
    commandHandlers["pnw"] = std::bind(&ServerMessageHandler::handleNewPlayer, this, std::placeholders::_1);
    commandHandlers["ppo"] = std::bind(&ServerMessageHandler::handlePlayerPosition, this, std::placeholders::_1);
    commandHandlers["plv"] = std::bind(&ServerMessageHandler::handlePlayerLevel, this, std::placeholders::_1);
    commandHandlers["pin"] = std::bind(&ServerMessageHandler::handlePlayerInventory, this, std::placeholders::_1);
    commandHandlers["pex"] = std::bind(&ServerMessageHandler::handleExpulsion, this, std::placeholders::_1);
    commandHandlers["pbc"] = std::bind(&ServerMessageHandler::handleBroadcast, this, std::placeholders::_1);
    commandHandlers["pic"] = std::bind(&ServerMessageHandler::handleIncantationStart, this, std::placeholders::_1);
    commandHandlers["pie"] = std::bind(&ServerMessageHandler::handleIncantationEnd, this, std::placeholders::_1);
    commandHandlers["pfk"] = std::bind(&ServerMessageHandler::handleEggLaying, this, std::placeholders::_1);
    commandHandlers["pdr"] = std::bind(&ServerMessageHandler::handleResourceDrop, this, std::placeholders::_1);
    commandHandlers["pgt"] = std::bind(&ServerMessageHandler::handleResourceCollect, this, std::placeholders::_1);
    commandHandlers["pdi"] = std::bind(&ServerMessageHandler::handlePlayerDeath, this, std::placeholders::_1);
    commandHandlers["enw"] = std::bind(&ServerMessageHandler::handleEggLaid, this, std::placeholders::_1);
    commandHandlers["ebo"] = std::bind(&ServerMessageHandler::handlePlayerConnectEgg, this, std::placeholders::_1);
    commandHandlers["edi"] = std::bind(&ServerMessageHandler::handleEggDeath, this, std::placeholders::_1);
    commandHandlers["sgt"] = std::bind(&ServerMessageHandler::handleTimeUnit, this, std::placeholders::_1);
    commandHandlers["sst"] = std::bind(&ServerMessageHandler::handleTimeUnitModification, this, std::placeholders::_1);
    commandHandlers["seg"] = std::bind(&ServerMessageHandler::handleEndGame, this, std::placeholders::_1);
    commandHandlers["smg"] = std::bind(&ServerMessageHandler::handleMessageFromServer, this, std::placeholders::_1);
    commandHandlers["suc"] = std::bind(&ServerMessageHandler::handleUnknownCommand, this, std::placeholders::_1);
    commandHandlers["sbp"] = std::bind(&ServerMessageHandler::handleCommandParameter, this, std::placeholders::_1);
}

void ServerMessageHandler::handleServerMessage(const std::string &message)
{
    std::string commandType = message.substr(0, 3);
    auto it = commandHandlers.find(commandType);

    if (it != commandHandlers.end()) {
        std::string commandBody = message.length() > 4 ? message.substr(4) : "";
        it->second(commandBody);
    } else {
        if (debug)
            std::cout << "Unhandled message: \"" << message << "\"" << std::endl;
    }
}

void ServerMessageHandler::handleMapSize(const std::string &message)
{
    int width, height;
    std::istringstream iss(message);

    if (!(iss >> width >> height)) {
        return handleCommandParameter(message);
    }
    display.getMap().resize(width, height);
    if (debug)
        std::cout << "Map size: " << width << "x" << height << std::endl;
}

void ServerMessageHandler::handleTileContent(const std::string &message)
{
    int x, y, q0, q1, q2, q3, q4, q5, q6;
    std::istringstream iss(message);

    if (!(iss >> x >> y >> q0 >> q1 >> q2 >> q3 >> q4 >> q5 >> q6)) {
        return handleCommandParameter(message);
    }
    // if (debug)
    //     std::cout << "Tile (" << x << ", " << y << "): " << q0 << " " << q1 << " " << q2 << " " << q3 << " " << q4
    //               << " " << q5 << " " << q6 << std::endl;
    display.getMap().getTile(x, y).updateRessources(q0, q1, q2, q3, q4, q5, q6);
}

void ServerMessageHandler::handleTeamNames(const std::string &message)
{
    if (std::find(display.team.begin(), display.team.end(), message) == display.team.end())
        display.team.push_back(message);
    if (debug)
        std::cout << "Team name: " << message << std::endl;
}

void ServerMessageHandler::handleNewPlayer(const std::string &message)
{
    int playerNumber, x, y, orientation, level;
    std::string teamName;
    std::istringstream iss(message);

    if (!(iss >> playerNumber >> x >> y >> orientation >> level >> teamName)) {
        return handleCommandParameter(message);
    }

    std::vector<std::shared_ptr<Data::Player>> &players = display.getMap().getPlayers();
    players.emplace_back(std::make_shared<Data::Player>(
        x, y, static_cast<Data::Player::Direction>(orientation), playerNumber, teamName, level
    ));

    if (debug)
        std::cout << "New player #" << playerNumber << " joined at (" << x << ", " << y << ") with orientation "
                  << orientation << ", level " << level << ", and team " << teamName << "." << std::endl;
}

void ServerMessageHandler::handlePlayerPosition(const std::string &message)
{
    int playerNumber, x, y, orientation;
    std::istringstream iss(message);

    if (!(iss >> playerNumber >> x >> y >> orientation)) {
        return handleCommandParameter(message);
    }

    auto &players = display.getMap().getPlayers();
    for (auto &player : players) {
        if (player->getId() == playerNumber) {
            player->setPosition(x, y, static_cast<Data::Player::Direction>(orientation));
            if (!player->isHatched())
                player->spawn();
            break;
        }
    }
    if (debug)
        std::cout << "Player #" << playerNumber << " position: (" << x << ", " << y << ") orientation: " << orientation
                  << std::endl;
}

void ServerMessageHandler::handlePlayerLevel(const std::string &message)
{
    int playerNumber, level;
    std::istringstream iss(message);

    if (!(iss >> playerNumber >> level)) {
        return handleCommandParameter(message);
    }

    auto &players = display.getMap().getPlayers();
    for (auto &player : players) {
        if (player->getId() == playerNumber) {
            player->setLevel(level);
            if (!player->isHatched())
                player->spawn();
            break;
        }
    }

    if (debug)
        std::cout << "Player #" << playerNumber << " level: " << level << std::endl;
}

void ServerMessageHandler::handlePlayerInventory(const std::string &message)
{
    int playerNumber, x, y, q0, q1, q2, q3, q4, q5, q6;
    std::istringstream iss(message);

    if (!(iss >> playerNumber >> x >> y >> q0 >> q1 >> q2 >> q3 >> q4 >> q5 >> q6)) {
        return handleCommandParameter(message);
    }

    auto &players = display.getMap().getPlayers();
    for (auto &player : players) {
        if (player->getId() == playerNumber) {
            player->setPosition(x, y, player->getOrientation());
            player->getInventory().update(q0, q1, q2, q3, q4, q5, q6);
            if (!player->isHatched())
                player->spawn();
            break;
        }
    }

    if (debug)
        std::cout << "Player #" << playerNumber << " inventory: (" << x << ", " << y << ") " << q0 << " " << q1 << " "
                  << q2 << " " << q3 << " " << q4 << " " << q5 << " " << q6 << std::endl;
}

void ServerMessageHandler::handleExpulsion(const std::string &message)
{
    int playerNumber;
    std::istringstream iss(message);

    if (!(iss >> playerNumber)) {
        return handleCommandParameter(message);
    }

    std::vector<std::shared_ptr<Data::Player>> &players = display.getMap().getPlayers();
    players.erase(
        std::remove_if(
            players.begin(),
            players.end(),
            [playerNumber](const std::shared_ptr<Data::Player> &player) { return player->getId() == playerNumber; }
        ),
        players.end()
    );

    if (debug)
        std::cout << "Player #" << playerNumber << " is expelled" << std::endl;
}

void ServerMessageHandler::handleBroadcast(const std::string &message)
{
    int playerNumber;
    std::string broadcastMessage;
    std::istringstream iss(message);

    if (!(iss >> playerNumber)) {
        return handleCommandParameter(message);
    }
    getline(iss, broadcastMessage);

    display.addMessage(broadcastMessage, playerNumber);
    if (debug)
        std::cout << "Player #" << playerNumber << " broadcasted: " << broadcastMessage << std::endl;
}

void ServerMessageHandler::handleIncantationStart(const std::string &message)
{
    std::istringstream iss(message);
    int x, y, level;
    if (!(iss >> x >> y >> level)) {
        return handleCommandParameter(message);
    }

    std::vector<int> players;
    int playerNumber;
    while (iss >> playerNumber) {
        players.push_back(playerNumber);
    }

    std::vector<std::shared_ptr<Data::Player>> &playerList = display.getMap().getPlayers();
    for (int &playerId : players) {
        for (std::shared_ptr<Data::Player> &player : playerList) {
            if (player->getId() == playerId) {
                player->getIncantation().start(300 / display.getTimeUnit(), x, y);
                break;
                if (!player->isHatched())
                    player->spawn();
            }
        }
    }

    if (debug) {
        std::cout << "Incantation started at (" << x << ", " << y << ") with level " << level << " by players: ";
        for (int p : players) {
            std::cout << p << " ";
        }
        std::cout << std::endl;
    }
}

void ServerMessageHandler::handleIncantationEnd(const std::string &message)
{
    std::istringstream iss(message);
    int x, y, result;
    if (!(iss >> x >> y >> result)) {
        return handleCommandParameter(message);
    }

    auto &playerList = display.getMap().getPlayers();
    for (auto &player : playerList) {
        Data::Player::Incantation incantation = player->getIncantation();
        if (incantation.isStarted() && incantation.getTarget().x() == x && incantation.getTarget().y() == y) {
            incantation.end();
            if (!player->isHatched())
                player->spawn();
        }
    }

    if (debug)
        std::cout << "Incantation ended at (" << x << ", " << y << ") with result: " << (result ? "success" : "failure")
                  << std::endl;
}

void ServerMessageHandler::handleEggLaying(const std::string &message)
{
    int playerNumber;
    std::istringstream iss(message);

    if (!(iss >> playerNumber)) {
        return handleCommandParameter(message);
    }
    for (auto &player : display.getMap().getPlayers()) {
        if (player->getId() == playerNumber) {
            display.getMap().getEggs().emplace_back(std::make_shared<Data::Egg>(player->getPos(), playerNumber));
            if (!player->isHatched())
                player->spawn();
        } else {
            return;
        }
    }
    if (debug)
        std::cout << "Player #" << playerNumber << " has laid an egg" << std::endl;
}

void ServerMessageHandler::handleResourceDrop(const std::string &message)
{
    int playerNumber, resourceType;
    std::istringstream iss(message);

    if (!(iss >> playerNumber >> resourceType)) {
        return handleCommandParameter(message);
    }
    for (auto &player : display.getMap().getPlayers()) {
        if (player->getId() == playerNumber) {
            Data::Tile &tile = display.getMap().getTile(player->getPos());
            player->drop(tile, resourceType);
            if (!player->isHatched())
                player->spawn();
        } else {
            return;
        }
    }
    if (debug)
        std::cout << "Player #" << playerNumber << " dropped resource type " << resourceType << std::endl;
}

void ServerMessageHandler::handleResourceCollect(const std::string &message)
{
    int playerNumber, resourceType;
    std::istringstream iss(message);

    if (!(iss >> playerNumber >> resourceType)) {
        return handleCommandParameter(message);
    }
    for (auto &player : display.getMap().getPlayers()) {
        if (player->getId() == playerNumber) {
            Data::Tile &tile = display.getMap().getTile(player->getPos());
            player->loot(tile, resourceType);
            if (!player->isHatched())
                player->spawn();
        } else {
            return;
        }
    }
    if (debug)
        std::cout << "Player #" << playerNumber << " collected resource type " << resourceType << std::endl;
}

void ServerMessageHandler::handlePlayerDeath(const std::string &message)
{
    int playerNumber;
    std::istringstream iss(message);

    if (!(iss >> playerNumber)) {
        return handleCommandParameter(message);
    }

    auto &players = display.getMap().getPlayers();
    players.erase(
        std::remove_if(
            players.begin(),
            players.end(),
            [playerNumber](const std::shared_ptr<Data::Player> &player) { return player->getId() == playerNumber; }
        ),
        players.end()
    );
    if (debug)
        std::cout << "Player #" << playerNumber << " has died" << std::endl;
}

void ServerMessageHandler::handleEggLaid(const std::string &message)
{
    int eggNumber, playerNumber, x, y;
    std::istringstream iss(message);

    if (!(iss >> eggNumber >> playerNumber >> x >> y)) {
        return handleCommandParameter(message);
    }

    std::vector<std::shared_ptr<Data::Egg>> &eggs = display.getMap().getEggs();
    eggs.emplace_back(std::make_shared<Data::Egg>(Pos<int, 2>{x, y}, eggNumber));

    if (debug)
        std::cout << "Egg #" << eggNumber << " was laid by player #" << playerNumber << " at (" << x << ", " << y << ")"
                  << std::endl;
}

void ServerMessageHandler::handlePlayerConnectEgg(const std::string &message)
{
    int eggNumber;
    std::istringstream iss(message);

    if (!(iss >> eggNumber)) {
        return handleCommandParameter(message);
    }

    auto &eggs = display.getMap().getEggs();
    auto eggIter = std::remove_if(eggs.begin(), eggs.end(), [eggNumber](const std::shared_ptr<Data::Egg> &egg) {
        return (egg != nullptr && egg->getId() == eggNumber);
    });
    if (eggIter != eggs.end()) {
        if (*eggIter == nullptr)
            return;
        int x = (*eggIter)->getPosition().x();
        int y = (*eggIter)->getPosition().y();

        for (auto &player : display.getMap().getPlayers()) {
            if (player->isHatched())
                continue;
            player->spawn();
            player->setPosition(x, y, Data::Player::Direction::UNDEFINED);
            break;
        }
        eggs.erase(eggIter, eggs.end());

        if (debug)
            std::cout << "Player connected to egg #" << eggNumber << " at (" << x << ", " << y << ")." << std::endl;
    }
}

void ServerMessageHandler::handleEggDeath(const std::string &message)
{
    int eggNumber;
    std::istringstream iss(message);

    if (!(iss >> eggNumber)) {
        return handleCommandParameter(message);
    }

    auto &eggs = display.getMap().getEggs();
    eggs.erase(
        std::remove_if(
            eggs.begin(),
            eggs.end(),
            [eggNumber](const std::shared_ptr<Data::Egg> &egg) { return egg != nullptr && egg->getId() == eggNumber; }
        ),
        eggs.end()
    );

    if (debug)
        std::cout << "Egg #" << eggNumber << " has died." << std::endl;
}

void ServerMessageHandler::handleTimeUnit(const std::string &message)
{
    int timeUnit;
    std::istringstream iss(message);

    if (!(iss >> timeUnit)) {
        handleCommandParameter(message);
        return;
    }
    display.setTimeUnit(timeUnit);
    if (debug)
        std::cout << "Time unit set to " << timeUnit << std::endl;
}

void ServerMessageHandler::handleTimeUnitModification(const std::string &message)
{
    int timeUnit;
    std::istringstream iss(message);

    if (!(iss >> timeUnit)) {
        return handleCommandParameter(message);
    }
    display.setTimeUnit(timeUnit);
    if (debug)
        std::cout << "Time unit modified to " << timeUnit << std::endl;
}

void ServerMessageHandler::handleEndGame(const std::string &message)
{
    display.setEndGame({message});
    if (debug)
        std::cout << "Game over. Message: " << message << std::endl;
}

void ServerMessageHandler::handleMessageFromServer(const std::string &message)
{
    display.addMessage(message);
    if (message.find("eni ") == 0) {
        int eggNumber, x, y;
        std::istringstream iss(message.substr(4));

        if (!(iss >> eggNumber >> x >> y)) {
            return handleCommandParameter(message);
        }
        display.getMap().getEggs().emplace_back(std::make_shared<Data::Egg>(Pos<int, 2>{x, y}, eggNumber));
    }

    if (debug)
        std::cout << "Message from server: " << message << std::endl;
}

void ServerMessageHandler::handleUnknownCommand(const std::string &message)
{
    if (debug)
        std::cout << "Unknown command: \"" << message << "\"" << std::endl;
}

void ServerMessageHandler::handleCommandParameter(const std::string &message)
{
    if (debug)
        std::cout << "Bad parameter for command: " << message << std::endl;
}

} // namespace GUI
