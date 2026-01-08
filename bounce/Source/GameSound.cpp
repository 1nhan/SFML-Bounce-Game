#include "GameSound.h"

GameSound::GameSound()
    :music_{"Content/Music.mp3"},
    bounceSoundBuffer_{"Content/Bounce.mp3"},
    bounceSound_{bounceSoundBuffer_}
{
    music_.setVolume(25);
    music_.setLooping(true);
    music_.play(); 

    bounceSound_.setVolume(10);
}

auto GameSound::PlayBounceSound()    ->void
{
    bounceSound_.play();
}