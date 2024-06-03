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
{
    m_itemName[0] = "Food";
    m_itemName[1] = "Linemate";
    m_itemName[2] = "Deraumere";
    m_itemName[3] = "Sibur";
    m_itemName[4] = "Mendiane";
    m_itemName[5] = "Phiras";
    m_itemName[6] = "Thystame";
}

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
        lineCount += 2;
        for (std::size_t i = 0; i < m_itemName.size(); i++) {
            std::string name = m_itemName.at(i);
            std::string line = name.append(": ").append(std::to_string(m_item->getInventory()[i]));
            DrawText(line.c_str(), x, y + ((lineCount + i) * m_lineHeight), m_lineHeight, WHITE);
        }
    }
}

} // namespace GUI
