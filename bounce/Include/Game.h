#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Paddle.h"
#include "Ball.h"
#include "Config.h"
#include "GameStats.h"
#include "GameSound.h"
#include "Background.h"

class Game
{
public:
    Game();
    
    auto IsRunning      ()  const   ->bool; 
    auto ProcessEvents  ()          ->void; 
    auto Update         ()          ->void; 
    auto Render         ()          ->void; 
    auto GetGlobalBounds()  const   ->sf::FloatRect;
    auto Restart        ()          ->void;

private:
    sf::RenderWindow    window_         ;
    sf::Clock           clock_          ;
    Paddle              paddle_         ;
    
    // Ball                ball_   ;
    std::vector<Ball>   balls_          ;
    sf::Clock           ballSpawnClock_ ;

    // private method Handle Collision 
    auto HandleCollisions()          ->void;

    GameStats           stats_          ;
    GameSound           sound_          ;
    Background          background_     ;    
};

