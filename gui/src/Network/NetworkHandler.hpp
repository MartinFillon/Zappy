#pragma once
#include <atomic>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <asio.hpp>

class NetworkHandler {
public:
    NetworkHandler(const std::string& machine, int port);
    ~NetworkHandler();

    void start();
    void stop();
    bool getMessage(std::string &message);
    void sendMessage(const std::string &message);
    void waitConnection();

    void requestMapSize();
    void requestTileContent(int x, int y);
    void requestMapContent();
    void requestTeamNames();
    void requestPlayerPosition(int playerNumber);
    void requestPlayerLevel(int playerNumber);
    void requestPlayerInventory(int playerNumber);
    void sendBroadcast(const std::string &message);
    void requestTimeUnit();
    void modifyTimeUnit(int t);

private:
    void run();
    void receiveMessages();

    std::string machine;
    int port;
    asio::io_context io_context;
    asio::ip::tcp::socket socket;
    std::atomic<bool> running;
    std::thread networkThread;
    std::queue<std::string> mQ;
    std::mutex mutex;
    std::condition_variable cv;
    std::mutex socketMutex;
};
