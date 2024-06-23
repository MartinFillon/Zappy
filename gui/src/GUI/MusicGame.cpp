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

void MusicGame::load(const std::string &filepath)
{
    if (isLoaded) {
        unload();
    }
    m_music = LoadMusicStream(filepath.c_str());
    isLoaded = true;
    PlayMusicStream(m_music);
}

void MusicGame::unload()
{
    isLoaded = false;
}

void MusicGame::update()
{
    if (isLoaded) {
        UpdateMusicStream(m_music);
    }
}
