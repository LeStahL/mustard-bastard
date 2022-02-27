#include "MusicPlayer.hpp"

MusicPlayer::MusicPlayer(bool muted) : _muted(muted), _currentlyPlaying(nullptr)
{
    _gameSoundBuffer.loadFromFile("assets/senfschleife.mp3");
    _gameSound.setBuffer(_gameSoundBuffer);
}

void MusicPlayer::playSound(MusicPlayer::SoundType soundType)
{
    if (_muted)
        return;

    switch(soundType)
    {
        case MusicPlayer::SoundType::GameSound:
        _currentlyPlaying = &_gameSound;
        break;

        default:
        break;
    }

    if(_currentlyPlaying != nullptr)
    {
        _currentlyPlaying->setLoop(true);
        _currentlyPlaying->play();
    }
}

void MusicPlayer::pause()
{
    if(_currentlyPlaying != nullptr)
    {
        _currentlyPlaying->pause();
    }
}

void MusicPlayer::stop()
{
    if (_currentlyPlaying != nullptr)
    {
        _currentlyPlaying->stop();
        _currentlyPlaying = nullptr;
    }
}
