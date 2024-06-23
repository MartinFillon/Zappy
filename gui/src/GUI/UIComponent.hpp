/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** UIComponent
*/

#pragma once

class UIComponent {
public:
    virtual ~UIComponent() = default;

    virtual void display() const = 0;
    virtual void resize(int x, int y, int width, int height) {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }

protected:
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;
};
