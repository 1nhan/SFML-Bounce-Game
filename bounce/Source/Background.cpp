#include "Background.h"

Background::Background()
    :texture_{"Content/background.png"},
    sprite_{texture_}
{

}

auto Background::Draw(sf::RenderWindow& window_) const-> void 
{
    window_.draw(sprite_);
}