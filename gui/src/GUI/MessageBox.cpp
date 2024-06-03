/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** MessageBox
*/



#include "MessageBox.hpp"
#include <algorithm>
#include <iomanip>
#include <sstream>
#include "define.hpp"

MessageBox::MessageBox() : m_scrollOffset(0), m_lineHeight(20), m_totalLines(0), m_maxLines(0) {}

void MessageBox::addMessage(const std::string &message, int user)
{
    auto now = std::chrono::steady_clock::now();
    std::string userStr;

    if (user == SERVER) {
        userStr = "Server";
    } else {
        userStr = m_team[user];
    }

    std::string timeStr = formatTime(now);
    std::stringstream formattedMessage;
    formattedMessage << "[" << timeStr << "] " << userStr << ": " << message;

    m_formattedMessages.push_back({now, userStr, {formattedMessage.str()}});

    m_totalLines = 0;
    for (const auto &msg : m_formattedMessages) {
        m_totalLines += wrapText(msg.lines[0], m_lineHeight).size();
    }
}

std::string MessageBox::formatTime(const std::chrono::steady_clock::time_point &tp) const
{
    auto now_c = std::chrono::system_clock::to_time_t(
        std::chrono::system_clock::now() + (tp - std::chrono::steady_clock::now())
    );
    std::tm now_tm = *std::localtime(&now_c);
    std::stringstream ss;
    ss << std::put_time(&now_tm, "%H:%M:%S");
    return ss.str();
}

std::vector<std::string> MessageBox::wrapText(const std::string &text, int width, int fontSize) const
{
    std::vector<std::string> lines;
    std::string currentLine;
    std::istringstream wordStream(text);
    std::string word;
    while (wordStream >> word) {
        if (currentLine.empty()) {
            currentLine = word;
        } else {
            std::string testLine = currentLine + " " + word;
            int textWidth = MeasureText(testLine.c_str(), fontSize);
            if (textWidth > width) {
                lines.push_back(currentLine);
                currentLine = word;
            } else {
                currentLine = testLine;
            }
        }
    }

    if (!currentLine.empty()) {
        lines.push_back(currentLine);
    }

    return lines;
}

bool MessageBox::isMouseOver(int x, int y, int width, int height) const
{
    return CheckCollisionPointRec(
        GetMousePosition(),
        {static_cast<float>(x), static_cast<float>(y), static_cast<float>(width), static_cast<float>(height)}
    );
}

void MessageBox::scroll(int amount)
{
    int maxOffset = std::max(0, m_totalLines - m_maxLines);
    m_scrollOffset = std::clamp(m_scrollOffset + amount, 0, maxOffset);
}

void MessageBox::handleInput(int x, int y, int width, int height)
{
    if (!isMouseOver(x, y, width, height)) {
        return;
    }
    int scrollAmount = GetMouseWheelMove();
    if (scrollAmount != 0) {
        scroll(scrollAmount);
    }
}

void MessageBox::display(int x, int y, int width, int height)
{
    DrawRectangle(x, y, width, height, (Color){0, 0, 0, 200});

    m_maxLines = height / m_lineHeight;
    m_totalLines = 0;

    std::vector<std::vector<std::string>> wrappedMessages;
    for (const auto &msg : m_formattedMessages) {
        wrappedMessages.push_back(wrapText(msg.lines[0], width - 20, m_lineHeight)); // Adjust width for scrollbar
        m_totalLines += wrappedMessages.back().size();
    }

    // Draw scrollbar
    float scrollbarHeight =
        static_cast<float>(height) * (static_cast<float>(m_maxLines) / static_cast<float>(m_totalLines));
    float scrollbarY = y + (static_cast<float>(m_scrollOffset) / static_cast<float>(m_totalLines)) * height;
    DrawRectangle(x + width - 20, y, 20, height, (Color){255, 255, 255, 50});
    DrawRectangle(x + width - 20, scrollbarY, 20, scrollbarHeight, (Color){255, 255, 255, 100});

    int startLine = std::max(0, m_totalLines - m_maxLines - m_scrollOffset);
    int currentLine = 0;
    int lineCount = 0;

    for (auto it = wrappedMessages.rbegin(); it != wrappedMessages.rend() && lineCount < m_maxLines; ++it) {
        const auto &msgLines = *it;

        for (const auto &line : msgLines) {
            if (currentLine >= startLine && lineCount < m_maxLines) {
                DrawText(line.c_str(), x, y + (lineCount * m_lineHeight), m_lineHeight, WHITE);
                lineCount++;
            }
            currentLine++;
        }
    }
}
