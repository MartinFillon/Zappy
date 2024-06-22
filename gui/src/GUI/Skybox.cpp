/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** Skybox
*/

#include "Skybox.hpp"

Skybox::Skybox() : isLoaded(false) {}

Skybox::~Skybox()
{
}

void Skybox::Load(const std::string &filepath)
{
    if (isLoaded) {
        UnloadModel();
    }
    model = LoadModel(filepath.c_str());
    isLoaded = true;
}

void Skybox::UnloadModel()
{
    isLoaded = false;
}

void Skybox::Draw()
{
    if (isLoaded) {
        DrawModel(model, (Vector3){5.0f, 50.0f, 5.0f}, 250.0f, WHITE);
    }
}
