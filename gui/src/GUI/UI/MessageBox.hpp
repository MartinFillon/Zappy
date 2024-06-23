/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** MessageBox
*/

#pragma once

#include <chrono>
#include <string>
#include <vector>
#include "UIComponent.hpp"

constexpr int SCROLL_WIDTH = 20;
constexpr int MAX_LINES = 100;

namespace GUI {
namespace UI {

class MessageBox : public UIComponent {
  public:
    MessageBox();
    void addMessage(const std::string &message, int user);
    void display() const override;
    void resize(int x, int y, int width, int height) override;
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
    mutable int m_totalLines;
    mutable int m_maxLines;
    std::vector<std::vector<std::string>> m_wrappedMessages;
    std::vector<FormattedMessage> m_formattedMessages;
    std::vector<std::string> m_team;
    int x, y, width, height;
};

} // namespace UI
} // namespace GUI
