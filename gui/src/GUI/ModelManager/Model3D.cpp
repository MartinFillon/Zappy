/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Model3D
*/

#include "Model3D.hpp"
#include <raylib.h>

Model3D::Model3D(const std::string &modelPath, const std::string &texturePath)
{
    model = LoadModel(modelPath.c_str());
    if (!texturePath.empty()) {
        texture = LoadTexture(texturePath.c_str());
        model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    }
}

Model3D::~Model3D()
{
}

void Model3D::Draw(Vector3 position, Vector3 scale, Vector3 rotationAxis, float rotationAngle, Color color) const
{
    DrawModelEx(model, position, rotationAxis, rotationAngle, scale, color);
}

void Model3D::SetTexture(const char *texturePath)
{
    UnloadTexture(texture);
    texture = LoadTexture(texturePath);
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
}
