/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** MessageBox
*/

#pragma once

#include <raylib.h>
#include <string>
#include <tuple>
#include <vector>
#include <chrono>

class MessageBox {
public:
    MessageBox(int x, int y, int width, int height);
    void addMessage(const std::string &message, int user);
    void display() const;
    void scroll(int amount);
    bool isMouseOver() const;
    void handleInput();

private:
    std::string formatTime(const std::chrono::steady_clock::time_point &tp) const;
    std::vector<std::string> wrapText(const std::string &text, int width, int fontSize) const;

    int x, y, width, height;
    int scrollOffset;
    int lineHeight;
    std::vector<std::tuple<std::chrono::steady_clock::time_point, int, std::string>> messages;
    std::vector<std::string> team;
};
