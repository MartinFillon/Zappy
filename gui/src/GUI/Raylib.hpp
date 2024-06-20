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
    struct Square {
        float x;
        float y;
        float size;
    };

    struct Circle {
        float centerX;
        float centerY;
        float radius;
    };

// Check Collision
    bool checkCollisionMouseCircle(float x, float y, float radius);
    bool checkCollisionMouseCircle(const Vector2 &vec, float radius);
    bool checkCollisionMouseRec(float x, float y, float width, float height);
    bool checkCollisionMouseRec(const Rectangle &rec);
    bool checkCollisionMouseSquare(float x, float y, float size);
    bool checkCollisionMouseSquare(const Square &sqr);

// Get RayCollision
    RayCollision getRayCollisionSphere(const Ray &ray, float x, float y, float z, float radius);
    RayCollision getRayCollisionSphere(const Ray &ray, const Vector3 &vec, float radius);
    RayCollision getRayCollisionBox(const Ray &ray, const Vector3 &pStart, const Vector3 &pEnd);
    RayCollision getRayCollisionCube(const Ray &ray, const Vector3 &pStart, float size);
    Ray GetMouseRay(const Camera3D &cam);

// Get
    Vector2 getMeasureTextEx(const std::string &str, int fontSize);

// Draw
    void draw(const Rectangle &rec, Color color);
    void draw(const Square &rec, Color color);
    void draw(const Circle &circle, Color color);
    void drawTextInForm(const std::string &str, const Rectangle &rec, int fontSize, Color color);
    void drawRectangle(float x, float y, float width, float height, Color color);
    void drawSquare(float x, float y, float size, Color color);
    void drawSquare(Square sqr, Color color);
    void drawRectangleLines(float x, float y, float width, float height, Color color);
    void drawSquareLines(float x, float y, float size, Color color);
    void drawSquareLines(Square sqr, Color color);
    void drawCircle(float x, float y, float radius, Color color);
    void drawCircle(const Vector2 &vec, float radius, Color color);
    void drawGrid(int slices, float spacing);
    void drawCuboid(const Vector3 &pStart, const Vector3 &pEnd, Color color);
    void drawCuboidWires(const Vector3 &pStart, const Vector3 &pEnd, Color color);
    void drawCube(const Vector3 &p, float size, Color color);
    void drawCubeWires(const Vector3 &p, float size, Color color);
    void drawSphere(const Vector3 &p, float radius, Color color);
    void drawText(const std::string &str, int x, int y, int fontSize, Color color);
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
    void beginMode3D(const Camera &cam);
    void endMode3D();
    float getFrameTime();

// Other
    Vector2 getMousePosition();

} // namespace Raylib
