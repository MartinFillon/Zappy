/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Model3D
*/



#pragma once

#include <raylib.h>
#include <string>

class Model3D {
  public:
    Model3D() {}
    Model3D(const std::string &modelPath, const std::string &texturePath = "");
    ~Model3D();

    void Draw(Vector3 position, Vector3 scale, Vector3 rotationAxis, float rotationAngle) const;
    void SetTexture(const char *texturePath);

  private:
    Model model;
    Texture2D texture;
};
