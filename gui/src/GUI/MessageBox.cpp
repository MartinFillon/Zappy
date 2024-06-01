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

MessageBox::MessageBox(int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height), scrollOffset(0), lineHeight(20)
{
}

void MessageBox::addMessage(const std::string &message, int user)
{
    messages.push_back(std::make_tuple(std::chrono::steady_clock::now(), user, message));
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
        std::string testLine = currentLine + (currentLine.empty() ? "" : " ") + word;
        int textWidth = MeasureText(testLine.c_str(), fontSize);
        if (textWidth > width) {
            lines.push_back(currentLine);
            currentLine = word;
        } else {
            currentLine = testLine;
        }
    }

    if (!currentLine.empty()) {
        lines.push_back(currentLine);
    }

    return lines;
}

bool MessageBox::isMouseOver() const
{
    return CheckCollisionPointRec(
        GetMousePosition(),
        {static_cast<float>(x), static_cast<float>(y), static_cast<float>(width), static_cast<float>(height)}
    );
}

void MessageBox::scroll(int amount)
{
    scrollOffset = std::max(0, scrollOffset + amount);
}

void MessageBox::handleInput()
{
    if (!isMouseOver()) {
        return;
    }
    int scrollAmount = GetMouseWheelMove();
    if (scrollAmount != 0) {
        scroll(scrollAmount);
    }
}

void MessageBox::display() const
{
    DrawRectangle(x, y, width, height, (Color){0, 0, 0, 200});

    int maxLines = height / lineHeight;
    int messageCount = messages.size();
    int totalLines = 0;
    for (const auto &message : messages) {
        auto time = std::get<0>(message);
        auto user = std::get<1>(message);
        auto text = std::get<2>(message);

        std::string timeStr = formatTime(time);
        std::stringstream formattedMessage;
        formattedMessage << "[" << timeStr << "] " << user << ": " << text;

        std::vector<std::string> wrappedText = wrapText(formattedMessage.str(), width, lineHeight);
        totalLines += wrappedText.size();
    }

    int startLine = std::max(0, totalLines - maxLines - scrollOffset);
    int currentLine = 0;
    int lineCount = 0;

    for (int i = messageCount - 1; i >= 0 && lineCount < maxLines; --i) {
        auto &message = messages[i];

        std::chrono::time_point time = std::get<0>(message);
        int user = std::get<1>(message);
        std::string text = std::get<2>(message);

        std::string timeStr = formatTime(time);
        std::stringstream formattedMessage;
        formattedMessage << "[" << timeStr << "] " << user << ": " << text;

        std::vector<std::string> wrappedText = wrapText(formattedMessage.str(), width, lineHeight);

        for (const auto &line : wrappedText) {
            if (currentLine >= startLine && lineCount < maxLines) {
                DrawText(line.c_str(), x, y + (lineCount * lineHeight), lineHeight, WHITE);
                lineCount++;
            }
            currentLine++;
        }
    }
}
