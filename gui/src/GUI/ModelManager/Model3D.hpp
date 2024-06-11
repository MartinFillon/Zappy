/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Model3D
*/



#pragma once

#include <raylib.h>

class Model3D {
  public:
    Model3D(const char *modelPath, const char *texturePath = nullptr);
    ~Model3D();

    void Draw(Vector3 position, Vector3 scale, Vector3 rotationAxis, float rotationAngle) const;
    void SetTexture(const char *texturePath);

  private:
    Model model;
    Texture2D texture;
};
