/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** Skybox
*/

#pragma once

#include <string>
#include "raylib.h"

constexpr std::string_view DEFAULT_SKYBOX_PATH = "gui/assets/skybox/skybox.gltf";

class Skybox {
  public:
    Skybox();
    ~Skybox();

    void Load(const std::string &filepath = std::string(DEFAULT_SKYBOX_PATH));
    void Draw();

  private:
    Model model;
    bool isLoaded;

    void UnloadModel();
};