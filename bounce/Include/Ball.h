#pragma once

#include<SFML/Graphics.hpp>
#include"Config.h"

class Ball
{
public:
    Ball();
    
    auto Move(float deltaTime)                              -> void         ;
    auto Draw(sf::RenderWindow& window_) const              -> void         ;
    auto GetGlobalBounds() const                            ->sf::FloatRect ;
    auto GetDirection() const                               ->sf::Vector2f  ;
    auto Bounce()                                           -> void         ;
    auto IsOutside() const                                  -> bool         ;
private:
    sf::CircleShape shape_      ;
    sf::Vector2f    direction_  ;
    float           speed_      ;  
        
};