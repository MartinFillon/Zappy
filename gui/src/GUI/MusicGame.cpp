/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** MusicGame
*/

#include "MusicGame.hpp"

MusicGame::MusicGame() : isLoaded(false)
{
    InitAudioDevice();
}

MusicGame::~MusicGame()
{
}

void MusicGame::load(const std::string &filepath_music,
    const std::string &filepath_sound)
{
    if (isLoaded) {
        unload();
    }
    m_music = LoadMusicStream(filepath_music.c_str());
    m_sound = LoadSound(filepath_sound.c_str());
    isLoaded = true;
    PlayMusicStream(m_music);
}

void MusicGame::unload()
{
    isLoaded = false;
}

void MusicGame::updateMusic()
{
    if (isLoaded) {
        UpdateMusicStream(m_music);
    }
}

void MusicGame::playSound()
{
    if (isLoaded) {
        PlaySound(m_sound);
    }
}
