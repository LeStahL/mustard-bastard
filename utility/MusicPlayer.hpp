#pragma once

#include <SFML/Audio.hpp>

#include <vector>

class MusicPlayer
{
    sf::SoundBuffer _gameSoundBuffer;
    sf::SoundBuffer _menuSoundBuffer;
    sf::SoundBuffer _highScoreSoundBuffer;
    sf::Sound _gameSound;
    sf::Sound _menuSound;
    sf::Sound _highScoreSound;
    sf::Sound *_currentlyPlaying;
    bool _muted;

    public:
    MusicPlayer(bool muted);
    MusicPlayer() : MusicPlayer(false) {}

    enum SoundType
    {
        GameSound,
        MenuSound,
        HighScoreSound
    };

    void playSound(SoundType soundType);
    void pause();
    void stop();
};
