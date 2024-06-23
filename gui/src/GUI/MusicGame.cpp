/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** MusicGame
*/

#include "MusicGame.hpp"

MusicGame::MusicGame() : m_volM(0.5f), m_volFx(0.5f), m_lastVolM(0.5f), m_lastVolFx(0.5f), isLoaded(false)
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
    SetMusicVolume(m_music, m_volM);
    SetSoundVolume(m_sound, m_volFx);
}

void MusicGame::unload()
{
    isLoaded = false;
}

void MusicGame::updateMusic()
{
    if (isLoaded) {
        if (m_lastVolM != m_volM) {
            SetMusicVolume(m_music, m_volM);
            m_lastVolM = m_volM;
        }
        UpdateMusicStream(m_music);
    }
}

void MusicGame::playSound()
{
    if (isLoaded) {
        if (m_lastVolFx != m_volFx) {
            SetSoundVolume(m_sound, m_volFx);
            m_lastVolFx = m_volFx;
        }
        PlaySound(m_sound);
    }
}

float &MusicGame::getVolumeMusic()
{
    return m_volM;
}

float &MusicGame::getVolumeFx()
{
    return m_volFx;
}
