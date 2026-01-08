#pragma once
#include<SFML/Audio.hpp>

class GameSound
{
public:
    GameSound();
    auto PlayBounceSound()    ->void;

private:
    sf::Music       music_;
    sf::SoundBuffer bounceSoundBuffer_;
    sf::Sound       bounceSound_;
};
