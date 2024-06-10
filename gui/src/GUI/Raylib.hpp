/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Tile
*/

#pragma once

#include <raylib.h>

namespace Raylib {

// Check Collision
    bool checkCollisionMouseCircle(float x, float y, float radius);
    bool checkCollisionMouseCircle(Vector2 vec, float radius);
    bool checkCollisionMouseRec(float x, float y, float width, float height);
    bool checkCollisionMouseRec(Rectangle rec);
    bool checkCollisionMouseSquare(float x, float y, float size);

// Get RayCollision
    RayCollision getRayCollisionSphere(Ray ray, float x, float y, float z, float radius);
    RayCollision getRayCollisionSphere(Ray ray, Vector3 vec, float radius);
    RayCollision getRayCollisionBox(Ray ray, Vector3 pStart, Vector3 pEnd);
    RayCollision getRayCollisionCube(Ray ray, Vector3 pStart, float size);
    Ray GetMouseRay(Camera3D cam);

// Draw
    void drawRectangle(float x, float y, float width, float height, Color color);
    void drawSquare(float x, float y, float size, Color color);
    void drawRectangleLines(float x, float y, float width, float height, Color color);
    void drawSquareLines(float x, float y, float size, Color color);
    void drawCircle(float x, float y, float radius, Color color);
    void drawCircle(Vector2 vec, float radius, Color color);

// Event
    bool isKeyPressed(int key);

// Window
    void disableCursor();
    void enableCursor();

} // namespace Raylib
