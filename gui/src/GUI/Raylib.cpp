/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Tile
*/

#include "Raylib.hpp"

bool Raylib::checkCollisionMouseCircle(float x, float y, float radius) {
    return CheckCollisionPointCircle(GetMousePosition(), {x, y}, radius);
}

bool Raylib::checkCollisionMouseCircle(Vector2 vec, float radius) {
    return CheckCollisionPointCircle(GetMousePosition(), vec, radius);
}

bool Raylib::checkCollisionMouseRec(float x, float y, float width, float height) {
    return CheckCollisionPointRec(GetMousePosition(), {x, y, width, height});
}

bool Raylib::checkCollisionMouseRec(Rectangle rec) {
    return CheckCollisionPointRec(GetMousePosition(), rec);
}

bool Raylib::checkCollisionMouseSquare(float x, float y, float size) {
    return CheckCollisionPointRec(GetMousePosition(), {x, y, size, size});
}

RayCollision Raylib::getRayCollisionSphere(Ray ray, float x, float y, float z, float radius) {
    return GetRayCollisionSphere(ray, {x, y, z}, radius);
}

RayCollision Raylib::getRayCollisionSphere(Ray ray, Vector3 vec, float radius) {
    return GetRayCollisionSphere(ray, vec, radius);
}

RayCollision Raylib::getRayCollisionBox(Ray ray, Vector3 pStart, Vector3 pEnd) {
    return GetRayCollisionBox(ray, (BoundingBox){pStart, pEnd});
}

RayCollision Raylib::getRayCollisionCube(Ray ray, Vector3 pStart, float size) {
    return GetRayCollisionBox(ray, (BoundingBox){
        (Vector3){pStart.x - size / 2.0f, pStart.y - size / 2.0f, pStart.z - size / 2.0f},
        (Vector3){pStart.x + size / 2.0f, pStart.y + size / 2.0f, pStart.z + size / 2.0f}});
}

Ray Raylib::GetMouseRay(Camera3D cam) {
    return GetMouseRay(GetMousePosition(), cam);
}

void Raylib::drawRectangle(float x, float y, float width, float height, Color color) {
    DrawRectangle(x, y, width, height, color);
}

void Raylib::drawSquare(float x, float y, float size, Color color) {
    DrawRectangle(x, y, size, size, color);
}

void Raylib::drawRectangleLines(float x, float y, float width, float height, Color color) {
    DrawRectangleLines(x, y, width, height, color);
}

void Raylib::drawSquareLines(float x, float y, float size, Color color) {
    DrawRectangleLines(x, y, size, size, color);
}

void Raylib::drawCircle(float x, float y, float radius, Color color) {
    DrawCircle(x, y, radius, color);
}

void Raylib::drawCircle(Vector2 vec, float radius, Color color) {
    DrawCircle(vec.x, vec.y, radius, color);
}

bool Raylib::isKeyPressed(int key) {
    return IsKeyPressed(key);
}

void Raylib::disableCursor() {
    DisableCursor();
}

void Raylib::enableCursor() {
    EnableCursor();
}
