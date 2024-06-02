/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** InfoBox
*/

#include <algorithm>
#include <iomanip>
#include <sstream>

#include "InfoBox.hpp"
#include "define.hpp"

namespace GUI {

InfoBox::InfoBox(): m_posTile({0, 0}), m_lineHeight(20)
{}

bool InfoBox::isPrint() const
{
    return m_isPrint;
}

void InfoBox::setPrint(bool print)
{
    m_isPrint = print;
}

Pos<float, 2> InfoBox::getPosTile() const
{
    return m_posTile;
}

void InfoBox::setPosTile(Pos<float, 2> posTile)
{
    m_posTile = posTile;
}

void InfoBox::setPosTile(float x, float y)
{
    m_posTile = {x, y};
}

float InfoBox::getSize() const
{
    return m_size;
}

void InfoBox::setSize(float size)
{
    m_size = size;
}

std::shared_ptr<Data::ISelectItem> &InfoBox::getItem()
{
    return m_item;
}

std::shared_ptr<Data::ISelectItem> InfoBox::getItem() const
{
    return m_item;
}

void InfoBox::display(int x, int y, int width, int height) const
{
    if (m_isPrint && m_item != nullptr) {
        DrawRectangle(x, y, width, height, (Color){0, 0, 0, 200});
        auto infoList = m_item->getStringInfo();
        int lineCount = 0;

        for (auto line : infoList) {
            DrawText(line.c_str(), x, y + (lineCount * m_lineHeight), m_lineHeight, WHITE);
            lineCount += 1;
        }
    }
}

} // namespace GUI
