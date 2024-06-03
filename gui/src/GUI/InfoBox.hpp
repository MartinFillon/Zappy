/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** InfoBox
*/

#pragma once

#include <chrono>
#include <raylib.h>
#include <string>
#include <vector>
#include <memory>

#include "Data/ISelectItem.hpp"

namespace GUI
{
    class InfoBox {
        public:
            InfoBox();

            bool isPrint() const;
            void setPrint(bool print);

            Pos<float, 2> getPosTile() const;
            void setPosTile(Pos<float, 2> posTile);
            void setPosTile(float x, float y);

            float getSize() const;
            void setSize(float size);

            std::shared_ptr<Data::ISelectItem> &getItem();
            std::shared_ptr<Data::ISelectItem> getItem() const;

            void display(int x, int y, int width, int height) const;

        private:
            bool m_isPrint;
            std::shared_ptr<Data::ISelectItem> m_item;
            Pos<float, 2> m_posTile;
            float m_size;

            std::array<std::string, 7> m_itemName;
            int m_lineHeight;
    };
}
