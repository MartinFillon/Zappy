/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** NetworkHandler
*/

#include "Handler.hpp"
#include <asio/error.hpp>
#include <chrono>
#include <iostream>

namespace Network {

Handler::Handler(const std::string &machine, int port)
    : machine(machine), port(port), io_context(), socket(io_context), running(false), handlerEnd(false)
{
}

Handler::~Handler()
{
    stop();
}

bool Handler::isRunning() const
{
    return running;
}

bool Handler::start()
{
    if (running) {
        return true;
    }
    try {
        asio::ip::tcp::resolver resolver(io_context);
        asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(machine, std::to_string(port));
        asio::connect(socket, endpoints);
        running = true;
        networkThread = std::thread(&Handler::run, this);
        return true;
    } catch (const std::exception &e) {
        std::cerr << "Network error: " << e.what() << std::endl;
        running = false;
        return false;
    }
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

    try {
        asio::error_code error;
        asio::write(socket, asio::buffer(message + "\n"), error);
        if (error == asio::error::broken_pipe) {
            if (running == false)
                return;
            std::cerr << "Connection closed by peer" << std::endl;
            running = false;
        } else if (error) {
            throw asio::system_error(error);
        }
    } catch (const std::exception &e) {
        if (running == false)
            return;
        std::cerr << "Send error: " << e.what() << std::endl;
        running = false;
    }
}


void Handler::run()
{
    std::string message;
    std::thread receiver;

    try {
        receiver = std::thread(&Handler::receiveMessages, this);
        sendMessage("GRAPHIC");
        while (message != "WELCOME" && running) {
            getMessage(message);
        }

        while (!handlerEnd) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            requestMapSize();
            requestMapContent();
            requestTimeUnit();
        }
    } catch (const std::exception &e) {
        running = false;
    }

    if (receiver.joinable()) {
        receiver.join();
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

            if (error == asio::error::eof) {
                if (running == true)
                    std::cerr << "Connection closed by peer" << std::endl;
                running = false;
                break;
            } else if (error) {
                throw asio::system_error(error);
            }

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
                mQ.push(line);
                cv.notify_one();
                data.erase(0, pos + 1);
            }

            leftover = data;
        } catch (const std::exception &e) {
            std::cerr << "Receive error: " << e.what() << std::endl;
            running = false;
        }
    }
    handlerEnd = true;
}

} // namespace Network
