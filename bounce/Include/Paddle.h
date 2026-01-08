#pragma once
#include<SFML/Graphics.hpp>
#include"Config.h"

class Paddle
{
private:

    sf::RectangleShape shape_;

public:
    Paddle();

    auto Draw           (sf::RenderWindow& window_) const  -> void;
    auto Move           (float deltaTime)                  -> void;
    auto GetGlobalBounds()                          const  ->sf::FloatRect;
    
};