/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Model3D
*/

#include "Model3D.hpp"

Model3D::Model3D(const char *modelPath, const char *texturePath)
{
    model = LoadModel(modelPath);
    if (texturePath) {
        texture = LoadTexture(texturePath);
        model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    }
}

Model3D::~Model3D()
{
    UnloadModel(model);
    UnloadTexture(texture);
}

void Model3D::Draw(Vector3 position, Vector3 scale, Vector3 rotationAxis, float rotationAngle) const
{
    DrawModelEx(model, position, rotationAxis, rotationAngle, scale, WHITE);
}

void Model3D::SetTexture(const char *texturePath)
{
    UnloadTexture(texture);
    texture = LoadTexture(texturePath);
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
}
