#pragma once
#include<SFML/Graphics.hpp>

class Background
{
public:
    Background();
    auto Draw(sf::RenderWindow& window_) const-> void ;

private:
    sf::Texture texture_;
    sf::Sprite  sprite_;
};