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

GUI::InfoBox::InfoBox()
{}

void GUI::InfoBox::display(int x, int y, int width, int height) const
{
    DrawRectangle(x, y, width, height, (Color){0, 0, 0, 200});
}

