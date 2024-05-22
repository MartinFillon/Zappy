/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ServerMessageHandler
*/

#include <iostream>
#include <sstream>

#include "Display.hpp"
#include "ServerMessageHandler.hpp"

namespace GUI {

ServerMessageHandler::ServerMessageHandler(bool debug, Display &display) : debug(debug), display(display)
{
    commandHandlers["msz"] = std::bind(&ServerMessageHandler::handleMapSize, this, std::placeholders::_1);
    commandHandlers["bct"] = std::bind(&ServerMessageHandler::handleTileContent, this, std::placeholders::_1);
    commandHandlers["tna"] = std::bind(&ServerMessageHandler::handleTeamNames, this, std::placeholders::_1);
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
    commandHandlers["eht"] = std::bind(&ServerMessageHandler::handleEggHatch, this, std::placeholders::_1);
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
        std::cout << "Unhandled message: " << message << std::endl;
    }
}

void ServerMessageHandler::handleMapSize(const std::string &message)
{
    int width, height;
    std::istringstream iss(message);
    iss >> width >> height;
    std::cout << "Map size: " << width << "x" << height << std::endl;
}

void ServerMessageHandler::handleTileContent(const std::string &message)
{
    int x, y, q0, q1, q2, q3, q4, q5, q6;
    std::istringstream iss(message);
    iss >> x >> y >> q0 >> q1 >> q2 >> q3 >> q4 >> q5 >> q6;
    std::cout << "Tile (" << x << ", " << y << "): " << q0 << " " << q1 << " " << q2 << " " << q3 << " " << q4 << " "
              << q5 << " " << q6 << std::endl;
}

void ServerMessageHandler::handleTeamNames(const std::string &message)
{
    std::cout << "Team name: " << message << std::endl;
}

void ServerMessageHandler::handlePlayerPosition(const std::string &message)
{
    int playerNumber, x, y, orientation;
    std::istringstream iss(message);
    iss >> playerNumber >> x >> y >> orientation;
    std::cout << "Player #" << playerNumber << " position: (" << x << ", " << y << ") orientation: " << orientation
              << std::endl;
}

void ServerMessageHandler::handlePlayerLevel(const std::string &message)
{
    int playerNumber, level;
    std::istringstream iss(message);
    iss >> playerNumber >> level;
    std::cout << "Player #" << playerNumber << " level: " << level << std::endl;
}

void ServerMessageHandler::handlePlayerInventory(const std::string &message)
{
    int playerNumber, x, y, q0, q1, q2, q3, q4, q5, q6;
    std::istringstream iss(message);
    iss >> playerNumber >> x >> y >> q0 >> q1 >> q2 >> q3 >> q4 >> q5 >> q6;
    std::cout << "Player #" << playerNumber << " inventory: (" << x << ", " << y << ") " << q0 << " " << q1 << " " << q2
              << " " << q3 << " " << q4 << " " << q5 << " " << q6 << std::endl;
}

void ServerMessageHandler::handleExpulsion(const std::string &message)
{
    int playerNumber;
    std::istringstream iss(message);
    iss >> playerNumber;
    std::cout << "Player #" << playerNumber << " was expelled." << std::endl;
}

void ServerMessageHandler::handleBroadcast(const std::string &message)
{
    std::cout << "Broadcast message: " << message << std::endl;
}

void ServerMessageHandler::handleIncantationStart(const std::string &message)
{
    int x, y, level;
    std::istringstream iss(message);
    iss >> x >> y >> level;
    std::cout << "Incantation started at (" << x << ", " << y << ") for level " << level << std::endl;
}

void ServerMessageHandler::handleIncantationEnd(const std::string &message)
{
    int x, y, result;
    std::istringstream iss(message);
    iss >> x >> y >> result;
    std::cout << "Incantation ended at (" << x << ", " << y << ") with result " << result << std::endl;
}

void ServerMessageHandler::handleEggLaying(const std::string &message)
{
    int playerNumber;
    std::istringstream iss(message);
    iss >> playerNumber;
    std::cout << "Player #" << playerNumber << " laid an egg." << std::endl;
}

void ServerMessageHandler::handleResourceDrop(const std::string &message)
{
    int playerNumber, resourceNumber;
    std::istringstream iss(message);
    iss >> playerNumber >> resourceNumber;
    std::cout << "Player #" << playerNumber << " dropped resource #" << resourceNumber << std::endl;
}

void ServerMessageHandler::handleResourceCollect(const std::string &message)
{
    int playerNumber, resourceNumber;
    std::istringstream iss(message);
    iss >> playerNumber >> resourceNumber;
    std::cout << "Player #" << playerNumber << " collected resource #" << resourceNumber << std::endl;
}

void ServerMessageHandler::handlePlayerDeath(const std::string &message)
{
    int playerNumber;
    std::istringstream iss(message);
    iss >> playerNumber;
    std::cout << "Player #" << playerNumber << " has died." << std::endl;
}

void ServerMessageHandler::handleEggLaid(const std::string &message)
{
    int eggNumber, playerNumber, x, y;
    std::istringstream iss(message);
    iss >> eggNumber >> playerNumber >> x >> y;
    std::cout << "Egg #" << eggNumber << " was laid by player #" << playerNumber << " at (" << x << ", " << y << ")"
              << std::endl;
}

void ServerMessageHandler::handleEggHatch(const std::string &message)
{
    int eggNumber;
    std::istringstream iss(message);
    iss >> eggNumber;
    std::cout << "Egg #" << eggNumber << " has hatched." << std::endl;
}

void ServerMessageHandler::handlePlayerConnectEgg(const std::string &message)
{
    int eggNumber;
    std::istringstream iss(message);
    iss >> eggNumber;
    std::cout << "Player connected to egg #" << eggNumber << std::endl;
}

void ServerMessageHandler::handleEggDeath(const std::string &message)
{
    int eggNumber;
    std::istringstream iss(message);
    iss >> eggNumber;
    std::cout << "Egg #" << eggNumber << " has died." << std::endl;
}

void ServerMessageHandler::handleTimeUnit(const std::string &message)
{
    int t;
    std::istringstream iss(message);
    iss >> t;
    std::cout << "Time unit: " << t << std::endl;
}

void ServerMessageHandler::handleTimeUnitModification(const std::string &message)
{
    int t;
    std::istringstream iss(message);
    iss >> t;
    std::cout << "Time unit modified to: " << t << std::endl;
}

void ServerMessageHandler::handleEndGame(const std::string &message)
{
    std::cout << "End of game. Winning team: " << message << std::endl;
}

void ServerMessageHandler::handleMessageFromServer(const std::string &message)
{
    std::cout << "Message from server: " << message << std::endl;
}

void ServerMessageHandler::handleUnknownCommand(const std::string &message)
{
    std::cout << "Unknown command received from server: " << message << std::endl;
}

void ServerMessageHandler::handleCommandParameter(const std::string &message)
{
    std::cout << "Command parameter issue: " << message << std::endl;
}

}; // namespace GUI
