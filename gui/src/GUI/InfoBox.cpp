/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** InfoBox
*/

#include "InfoBox.hpp"
#include "Raylib.hpp"

namespace GUI {

InfoBox::InfoBox(): m_posTile({0.0f, 0.0f, 0.0f}), m_size(0.0f), m_lineHeight(20)
{
    m_itemName = {"Food", "Linemate", "Deraumere", "Sibur", "Mendiane", "Phiras", "Thystame"};
}

bool InfoBox::isPrint() const
{
    return m_isPrint;
}

void InfoBox::setPrint(bool print)
{
    m_isPrint = print;
}

Pos<float, 3> InfoBox::getPosTile() const
{
    return m_posTile;
}

void InfoBox::setPosTile(Pos<float, 3> posTile)
{
    m_posTile = posTile;
}

void InfoBox::setPosTile(float x, float y, float z)
{
    m_posTile = {x, y, z};
}

float InfoBox::getSize() const
{
    return m_size;
}

void InfoBox::setSize(float size)
{
    m_size = size;
}

void InfoBox::setItem(std::shared_ptr<Data::ISelectItem> item)
{
    m_item = item;
}

std::shared_ptr<Data::ISelectItem> &InfoBox::getItem()
{
    return m_item;
}

std::shared_ptr<Data::ISelectItem> InfoBox::getItem() const
{
    return m_item;
}

void InfoBox::display() const
{
    if (m_isPrint && m_item != nullptr) {
        Raylib::drawRectangle(x, y, width, height, (Color){0, 0, 0, 200});
        auto infoList = m_item->getStringInfo();
        int lineCount = 0;

        for (auto line : infoList) {
            Raylib::drawText(line, x, y + (lineCount * m_lineHeight), m_lineHeight, WHITE);
            lineCount += 1;
        }
        lineCount += 2;
        for (std::size_t i = 0; i < m_itemName.size(); i++) {
            std::string name = m_itemName.at(i);
            std::string line = name.append(": ").append(std::to_string(m_item->getInventory()[i]));
            Raylib::drawText(line, x, y + ((lineCount + i) * m_lineHeight), m_lineHeight, WHITE);
        }
    }
}

} // namespace GUI
