/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Tile
*/

#include "Raylib.hpp"

namespace Raylib
{

bool checkCollisionMouseCircle(float x, float y, float radius)
{
    return CheckCollisionPointCircle(GetMousePosition(), {x, y}, radius);
}

bool checkCollisionMouseCircle(Vector2 vec, float radius)
{
    return CheckCollisionPointCircle(GetMousePosition(), vec, radius);
}

bool checkCollisionMouseRec(float x, float y, float width, float height)
{
    return CheckCollisionPointRec(GetMousePosition(), {x, y, width, height});
}

bool checkCollisionMouseRec(Rectangle rec)
{
    return CheckCollisionPointRec(GetMousePosition(), rec);
}

bool checkCollisionMouseSquare(float x, float y, float size)
{
    return CheckCollisionPointRec(GetMousePosition(), {x, y, size, size});
}

RayCollision getRayCollisionSphere(Ray ray, float x, float y, float z, float radius)
{
    return GetRayCollisionSphere(ray, {x, y, z}, radius);
}

RayCollision getRayCollisionSphere(Ray ray, Vector3 vec, float radius)
{
    return GetRayCollisionSphere(ray, vec, radius);
}

RayCollision getRayCollisionBox(Ray ray, Vector3 pStart, Vector3 pEnd)
{
    return GetRayCollisionBox(ray, (BoundingBox){pStart, pEnd});
}

RayCollision getRayCollisionCube(Ray ray, Vector3 pStart, float size)
{
    return GetRayCollisionBox(ray, (BoundingBox){
        (Vector3){pStart.x - size / 2.0f, pStart.y - size / 2.0f, pStart.z - size / 2.0f},
        (Vector3){pStart.x + size / 2.0f, pStart.y + size / 2.0f, pStart.z + size / 2.0f}});
}

Ray GetMouseRay(Camera3D cam)
{
    return GetMouseRay(GetMousePosition(), cam);
}

void drawRectangle(float x, float y, float width, float height, Color color)
{
    DrawRectangle(x, y, width, height, color);
}

void drawSquare(float x, float y, float size, Color color)
{
    DrawRectangle(x, y, size, size, color);
}

void drawRectangleLines(float x, float y, float width, float height, Color color)
{
    DrawRectangleLines(x, y, width, height, color);
}

void drawSquareLines(float x, float y, float size, Color color)
{
    DrawRectangleLines(x, y, size, size, color);
}

void drawCircle(float x, float y, float radius, Color color)
{
    DrawCircle(x, y, radius, color);
}

void drawCircle(Vector2 vec, float radius, Color color)
{
    DrawCircle(vec.x, vec.y, radius, color);
}

void drawGrid(int slices, float spacing)
{
    DrawGrid(slices, spacing);
}

void drawCuboid(Vector3 pStart, Vector3 pEnd, Color color)
{
    DrawCube(pStart, pEnd.x, pEnd.y, pEnd.z, color);
}

void drawCuboidWires(Vector3 pEnd, Vector3 pStart, Color color)
{
    DrawCubeWires(pStart, pEnd.x, pEnd.y, pEnd.z, color);
}

void drawCube(Vector3 p, float size, Color color)
{
    DrawCube(p, size, size, size, color);
}

void drawCubeWires(Vector3 p, float size, Color color)
{
    DrawCubeWires(p, size, size, size, color);
}

void drawSphere(Vector3 p, float radius, Color color)
{
    DrawSphere(p, radius, color);
}

void drawText(std::string str, int x, int y, int fontSize, Color color)
{
    DrawText(str.c_str(), x, y, fontSize, color);
}

void drawLine(int sx, int sy, int ex, int ey, Color color)
{
    DrawLine(sx, sy, ex, ey, color);
}

bool isMouseButtonPressed(int button)
{
    return IsMouseButtonPressed(button);
}

bool isKeyPressed(int key)
{
    return IsKeyPressed(key);
}

int getKeyPressed()
{
    return GetKeyPressed();
}

float getMouseWheelMove()
{
    return GetMouseWheelMove();
}

bool isMouseButtonDown(int button)
{
    return IsMouseButtonDown(button);
}

void disableCursor()
{
    DisableCursor();
}

void enableCursor()
{
    EnableCursor();
}

void updateCamera(Camera &cam, int mode)
{
    UpdateCamera(&cam, mode);
}

void clearBackground(Color color)
{
    ClearBackground(color);
}

void beginMode3D(Camera &cam)
{
    BeginMode3D(cam);
}

void endMode3D()
{
    EndMode3D();
}

float getFrameTime()
{
    return GetFrameTime();
}

Vector2 getMousePosition()
{
    return GetMousePosition();
}

} // namespace Raylib
