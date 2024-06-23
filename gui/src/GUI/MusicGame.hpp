/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** MusicGame
*/

#pragma once

#include <string>
#include "raylib.h"

constexpr char DEFAULT_MUSIC_PATH[] = "gui/music/game-music-loop.mp3";

class MusicGame {
  public:
    MusicGame();
    ~MusicGame();

    void load(const std::string &filepath = DEFAULT_MUSIC_PATH);
    void update();

  private:
    Music m_music;
    bool isLoaded;

    void unload();
};
