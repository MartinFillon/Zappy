/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Tile
*/

#pragma once

#include <raylib.h>
#include <string>

namespace Raylib {
    struct Circle {
        int centerX;
        int centerY;
        float radius;
    };

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

// Get
    Vector2 getMeasureTextEx(std::string &str, int fontSize);

// Draw
    void draw(Rectangle &rec, Color color);
    void draw(Circle &circle, Color color);
    void drawTextInForm(std::string &str, Rectangle &rec, int fontSize, Color color);
    void drawRectangle(float x, float y, float width, float height, Color color);
    void drawSquare(float x, float y, float size, Color color);
    void drawRectangleLines(float x, float y, float width, float height, Color color);
    void drawSquareLines(float x, float y, float size, Color color);
    void drawCircle(float x, float y, float radius, Color color);
    void drawCircle(Vector2 vec, float radius, Color color);
    void drawGrid(int slices, float spacing);
    void drawCuboid(Vector3 pStart, Vector3 pEnd, Color color);
    void drawCuboidWires(Vector3 pStart, Vector3 pEnd, Color color);
    void drawCube(Vector3 p, float size, Color color);
    void drawCubeWires(Vector3 p, float size, Color color);
    void drawSphere(Vector3 p, float radius, Color color);
    void drawText(std::string str, int x, int y, int fontSize, Color color);
    void drawLine(int sx, int sy, int ex, int ey, Color color);

// Event
    bool isMouseButtonPressed(int button);
    bool isKeyPressed(int key);
    int getKeyPressed();
    float getMouseWheelMove();
    bool isMouseButtonDown(int button);
    bool isMouseButtonReleased(int button);

// Window
    void disableCursor();
    void enableCursor();
    void updateCamera(Camera &cam, int mode);
    void clearBackground(Color color);
    void beginMode3D(Camera &cam);
    void endMode3D();
    float getFrameTime();

// Other
    Vector2 getMousePosition();

} // namespace Raylib
