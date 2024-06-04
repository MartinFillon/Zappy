/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Handler
*/

#pragma once
#include <asio.hpp>
#include <atomic>
#include <mutex>
#include <queue>
#include <thread>
#include <condition_variable>

#define BUFFER_LEN 1024

namespace Network {
/**
 * @class Handler
 * @brief Handles network communication with a server.
 *
 * The Handler class provides functionality to establish a network connection,
 * send and receive messages, and perform various requests to the server.
 */
class Handler {
  public:
    /**
     * @brief Constructs a Handler object with the specified machine and port.
     * @param machine The IP address or hostname of the server.
     * @param port The port number to connect to.
     */
    Handler(const std::string &machine, int port);

    /**
     * @brief Destructor for the Handler object.
     */
    ~Handler();

    /**
     * @brief Starts the network communication.
     * @return True if initialization succeeds, false otherwise.
     */
    bool start();

    /**
     * @brief Stops the network communication.
     */
    void stop();

    /**
     * @brief Retrieves the next message from the message queue.
     * @param message Reference to a string variable to store the retrieved message.
     * @return True if a message was retrieved successfully, false otherwise.
     */
    bool getMessage(std::string &message);

    /**
     * @brief Sends a message to the server.
     * @param message The message to send.
     */
    void sendMessage(const std::string &message);

    /**
     * @brief Requests the size of the map from the server.
     */
    void requestMapSize();

    /**
     * @brief Requests the content of a specific tile on the map from the server.
     * @param x The x-coordinate of the tile.
     * @param y The y-coordinate of the tile.
     */
    void requestTileContent(int x, int y);

    /**
     * @brief Requests the content of the entire map from the server.
     */
    void requestMapContent();

    /**
     * @brief Requests the names of the teams from the server.
     */
    void requestTeamNames();

    /**
     * @brief Requests the position of a specific player from the server.
     * @param playerNumber The number of the player.
     */
    void requestPlayerPosition(int playerNumber);

    /**
     * @brief Requests the level of a specific player from the server.
     * @param playerNumber The number of the player.
     */
    void requestPlayerLevel(int playerNumber);

    /**
     * @brief Requests the inventory of a specific player from the server.
     * @param playerNumber The number of the player.
     */
    void requestPlayerInventory(int playerNumber);

    /**
     * @brief Sends a broadcast message to all players on the server.
     * @param message The message to broadcast.
     */
    void sendBroadcast(const std::string &message);

    /**
     * @brief Requests the time unit from the server.
     */
    void requestTimeUnit();

    /**
     * @brief Modifies the time unit on the server.
     * @param t The new time unit value.
     */
    void modifyTimeUnit(int t);

  private:
    /**
     * @brief The main network communication loop.
     */
    void run();

    /**
     * @brief Receives messages from the server and adds them to the message queue.
     */
    void receiveMessages();

    std::string machine;          ///< The IP address or hostname of the server.
    int port;                     ///< The port number to connect to.
    asio::io_context io_context;  ///< The asio io_context for network operations.
    asio::ip::tcp::socket socket; ///< The TCP socket for communication with the server.
    std::atomic<bool> running;    ///< Flag indicating if the network communication is running.
    std::thread networkThread;    ///< The thread for running the network communication loop.
    std::queue<std::string> mQ;   ///< The message queue for storing received messages.
    std::mutex mutex;             ///< Mutex for protecting access to the message queue.
    std::condition_variable cv;   ///< Condition variable for synchronizing access to the message queue.
    std::mutex socketMutex;       ///< Mutex for protecting access to the socket.
};
} // namespace Network
