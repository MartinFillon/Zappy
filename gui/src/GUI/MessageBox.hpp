/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** MessageBox
*/

#pragma once

#include <chrono>
#include <raylib.h>
#include <string>
#include <vector>

class MessageBox {
  public:
    MessageBox();
    void addMessage(const std::string &message, int user);
    void display(int x, int y, int width, int height) const;
    void scroll(int amount);
    bool isMouseOver(int x, int y, int width, int height) const;
    void handleInput(int x, int y, int width, int height);

  private:
    struct FormattedMessage {
        std::chrono::steady_clock::time_point time;
        std::string user;
        std::vector<std::string> lines;
    };

    std::string formatTime(const std::chrono::steady_clock::time_point &tp) const;
    std::vector<std::string> wrapText(const std::string &text, int width, int fontSize) const;

    int m_scrollOffset;
    int m_lineHeight;
    std::vector<FormattedMessage> m_formattedMessages;
    std::vector<std::string> m_team;
};
