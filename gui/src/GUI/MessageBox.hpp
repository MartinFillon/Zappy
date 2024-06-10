/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** MessageBox
*/

#pragma once

#include <chrono>
#include "Raylib.hpp"
#include <string>
#include <vector>

class MessageBox {
  public:
    MessageBox();
    void addMessage(const std::string &message, int user);
    void display(int x, int y, int width, int height);
    void scroll(int amount);
    bool isMouseOver() const;
    bool isMouseOver(int x, int y, int width, int height) const;
    void handleInput();

  private:
    struct FormattedMessage {
        std::chrono::steady_clock::time_point time;
        std::string user;
        std::vector<std::string> lines;
    };

    std::string formatTime(const std::chrono::steady_clock::time_point &tp) const;
    std::vector<std::string> wrapText(const std::string &text, int width, int fontSize = 20) const;

    int m_scrollOffset;
    int m_lineHeight;
    int m_totalLines;
    int m_maxLines;
    std::vector<FormattedMessage> m_formattedMessages;
    std::vector<std::string> m_team;
    mutable int x, y, width, height;
};
