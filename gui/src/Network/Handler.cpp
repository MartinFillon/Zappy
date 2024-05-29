/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** NetworkHandler
*/

#include <iostream>

#include "Handler.hpp"

namespace Network {
Handler::Handler(const std::string &machine, int port)
    : machine(machine), port(port), io_context(), socket(io_context), running(false)
{
}

Handler::~Handler()
{
    stop();
}

void Handler::start()
{
    running = true;
    networkThread = std::thread(&Handler::run, this);
}

void Handler::stop()
{
    running = false;
    if (networkThread.joinable()) {
        networkThread.join();
    }
}

bool Handler::getMessage(std::string &message)
{
    std::scoped_lock lock(mutex);
    if (!mQ.empty()) {
        message = mQ.front();
        mQ.pop();
        return true;
    }
    return false;
}

void Handler::sendMessage(const std::string &message)
{
    std::scoped_lock lock(socketMutex);
    asio::write(socket, asio::buffer(message + "\n"));
}

void Handler::run()
{
    std::string message;

    try {
        asio::ip::tcp::resolver resolver(io_context);
        asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(machine, std::to_string(port));
        asio::connect(socket, endpoints);

        std::thread receiver(&Handler::receiveMessages, this);
        sendMessage("GRAPHIC");
        while (message != "WELCOME") {
            getMessage(message);
        }

        while (running) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            // requestMapSize();
            // requestTeamNames();
        }

        receiver.join();
    } catch (const std::exception &e) {
        std::cerr << "Network error: " << e.what() << std::endl;
        running = false;
    }
}

void Handler::receiveMessages()
{
    std::vector<char> buffer(BUFFER_LEN);
    std::string leftover;

    while (running) {
        try {
            asio::error_code error;
            size_t n = socket.read_some(asio::buffer(buffer), error);
            if (error)
                throw asio::system_error(error);
            std::string data(buffer.data(), n);
            data = leftover + data;
            leftover.clear();

            size_t pos = 0;
            while ((pos = data.find('\n')) != std::string::npos) {
                std::string line = data.substr(0, pos);
                if (!line.empty() && line.back() == '\r') {
                    line.pop_back();
                }
                std::scoped_lock lock(mutex);
                // debug print
                // std::cout << line << std::endl;
                mQ.push(line);
                cv.notify_one();
                data.erase(0, pos + 1);
            }

            leftover = data;
        } catch (const std::exception &e) {
            std::cerr << "Receive error: " << e.what() << std::endl;
            running = false;
            break;
        }
    }
}

}; // namespace Network
