/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** MessageBox
*/

#include <algorithm>
#include <iomanip>
#include <sstream>

#include "MessageBox.hpp"
#include "Raylib.hpp"
#include "define.hpp"

MessageBox::MessageBox()
    : m_scrollOffset(0), m_lineHeight(20), m_totalLines(0), m_maxLines(0), x(0), y(0), width(0), height(0)
{
}

void MessageBox::addMessage(const std::string &message, int user)
{
    auto now = std::chrono::steady_clock::now();
    std::string userStr;

    if (user == SERVER) {
        userStr = "Server";
    } else {
        if (user > static_cast<int>(m_team.size())) {
            userStr = "User #" + std::to_string(user);
        } else {
            userStr = "Unknown";
        }
    }

    std::string timeStr = formatTime(now);
    std::stringstream formattedMessage;
    formattedMessage << "[" << timeStr << "] " << userStr << ": " << message;

    m_formattedMessages.push_back({now, userStr, {formattedMessage.str()}});

    m_totalLines = 0;
    for (const auto &msg : m_formattedMessages) {
        m_totalLines += wrapText(msg.lines[0], m_lineHeight).size();
    }

    if (m_formattedMessages.size() > MAX_LINES) {
        m_formattedMessages.erase(m_formattedMessages.begin());
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

    auto pushLine = [&](const std::string &line) {
        if (!line.empty()) {
            lines.push_back(line);
        }
    };

    while (wordStream >> word) {
        if (currentLine.empty()) {
            currentLine = word;
        } else {
            std::string testLine = currentLine + " " + word;
            int textWidth = MeasureText(testLine.c_str(), fontSize);
            if (textWidth > width) {
                pushLine(currentLine);
                currentLine = word;
            } else {
                currentLine = testLine;
            }
        }
    }
    pushLine(currentLine);
    std::vector<std::string> finalLines;
    for (const auto &line : lines) {
        if (MeasureText(line.c_str(), fontSize) <= width) {
            finalLines.push_back(line);
        } else {
            std::string part;
            for (char ch : line) {
                std::string testPart = part + ch;
                if (MeasureText(testPart.c_str(), fontSize) > width) {
                    if (!part.empty()) {
                        finalLines.push_back(part);
                    }
                    part = ch;
                } else {
                    part = testPart;
                }
            }
            if (!part.empty()) {
                finalLines.push_back(part);
            }
        }
    }

    return finalLines;
}

bool MessageBox::isMouseOver() const
{
    return Raylib::checkCollisionMouseRec(
        static_cast<float>(x), static_cast<float>(y), static_cast<float>(width), static_cast<float>(height)
    );
}

bool MessageBox::isMouseOver(int x, int y, int width, int height) const
{
    return Raylib::checkCollisionMouseRec(
        static_cast<float>(x), static_cast<float>(y), static_cast<float>(width), static_cast<float>(height)
    );
}

void MessageBox::scroll(int amount)
{
    int maxOffset = std::max(0, m_totalLines - m_maxLines);
    m_scrollOffset = std::clamp(m_scrollOffset + amount, 0, maxOffset);
}

void MessageBox::handleInput()
{
    if (!isMouseOver()) {
        return;
    }
    int scrollAmount = Raylib::getMouseWheelMove();
    if (scrollAmount != 0) {
        scroll(-scrollAmount);
    }
    if (Raylib::isMouseButtonDown(MOUSE_BUTTON_LEFT) &&
        isMouseOver(x + width - SCROLL_WIDTH, y, SCROLL_WIDTH, height)) {
        int maxOffset = std::max(0, m_totalLines - m_maxLines);
        float clickPosition = Raylib::getMousePosition().y - y;
        float scrollbarHeight =
            static_cast<float>(height) * (static_cast<float>(m_maxLines) / static_cast<float>(m_totalLines));
        float scrollbarCenter = scrollbarHeight / 2;
        m_scrollOffset =
            std::clamp(static_cast<int>((clickPosition + scrollbarCenter) / height * maxOffset), 0, maxOffset);
    }
}

void MessageBox::resize(int x, int y, int width, int height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

void MessageBox::display()
{
    Raylib::drawRectangle(x, y, width, height, (Color){0, 0, 0, 200});

    m_maxLines = height / m_lineHeight;
    m_totalLines = 0;

    std::vector<std::vector<std::string>> wrappedMessages;
    for (const FormattedMessage &msg : m_formattedMessages) {
        wrappedMessages.push_back(wrapText(msg.lines[0], width - SCROLL_WIDTH, m_lineHeight));
        m_totalLines += wrappedMessages.back().size();
    }

    float scrollbarHeight = std::min(
        static_cast<float>(height) * (static_cast<float>(m_maxLines) / static_cast<float>(m_totalLines)),
        static_cast<float>(height)
    );
    float scrollbarY = y + (static_cast<float>(m_scrollOffset) / static_cast<float>(m_totalLines)) * height;
    Raylib::drawRectangle(x + width - SCROLL_WIDTH, y, SCROLL_WIDTH, height, (Color){255, 255, 255, 50});
    Raylib::drawRectangle(
        x + width - SCROLL_WIDTH, scrollbarY, SCROLL_WIDTH, scrollbarHeight, (Color){255, 255, 255, 100}
    );

    int startLine = std::max(0, m_totalLines - m_maxLines - m_scrollOffset);
    int currentLine = 0;
    int lineCount = 0;

    for (auto it = wrappedMessages.rbegin(); it != wrappedMessages.rend() && lineCount < m_maxLines; ++it) {
        const std::vector<std::string> &msgLines = *it;

        for (const auto &line : msgLines) {
            if (currentLine >= startLine && lineCount < m_maxLines) {
                Raylib::drawText(line, x, y + (lineCount * m_lineHeight), m_lineHeight, WHITE);
                lineCount++;
            }
            currentLine++;
        }
    }
}
