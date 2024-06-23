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
constexpr char DEFAULT_SOUND_PATH[] = "gui/music/computer-processing-sound-effects.mp3";

class MusicGame {
  public:
    MusicGame();
    ~MusicGame();

    void load(const std::string &filepath_music = DEFAULT_MUSIC_PATH,
      const std::string &filepath_sound = DEFAULT_SOUND_PATH);
    void updateMusic();
    void playSound();

    float &getVolumeMusic();
    float &getVolumeFx();

  private:
    float m_volM;
    float m_volFx;
    float m_lastVolM;
    float m_lastVolFx;
    Music m_music;
    Sound m_sound;
    bool isLoaded;

    void unload();
};
