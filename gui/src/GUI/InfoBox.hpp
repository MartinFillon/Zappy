/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** InfoBox
*/

#pragma once

#include <string>
#include <memory>

#include "Data/ISelectItem.hpp"

namespace GUI
{
    class InfoBox {
        public:
            InfoBox();
            InfoBox(InfoBox &other) = default;
            InfoBox &operator=(InfoBox &other) = default;

            bool isPrint() const;
            void setPrint(bool print);

            void resize(int x, int y, int width, int height);

            Pos<float, 3> getPosTile() const;
            void setPosTile(Pos<float, 3> posTile);
            void setPosTile(float x, float y, float z);

            float getSize() const;
            void setSize(float size);

            void setItem(std::shared_ptr<Data::ISelectItem> item);
            std::shared_ptr<Data::ISelectItem> &getItem();
            std::shared_ptr<Data::ISelectItem> getItem() const;

            void display() const;

        private:
            bool m_isPrint;
            std::shared_ptr<Data::ISelectItem> m_item;
            Pos<float, 3> m_posTile;
            float m_size;

            std::array<std::string, 7> m_itemName;
            int m_lineHeight;
            int m_x;
            int m_y;
            int m_width;
            int m_height;
    };
}
