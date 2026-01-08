#include <Paddle.h>
#include <algorithm>

Paddle::Paddle()
    :shape_{sf::Vector2f{120, 20}}
{
    shape_.setFillColor({71, 147, 135,255});
    shape_.setOrigin(shape_.getGeometricCenter());
    shape_.setOutlineThickness(3);
    shape_.setOutlineColor({4, 219, 15,255});
    shape_.setPosition({Config::WIN_WIDTH*Config::HALF, Config::WIN_HEIGHT*Config::THREE_QUARTERS});
}

auto Paddle::Draw(sf::RenderWindow& window_) const->void
{
    window_.draw(shape_);
}

auto Paddle::Move(float deltaTime) -> void
{

    sf::Vector2f prevposition  = shape_.getPosition(); 

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        shape_.move({+Config::USER_SPEED*deltaTime,Config::ZERO});
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        shape_.move({-Config::USER_SPEED*deltaTime,Config::ZERO});
    }
    
    float halfWidth = shape_.getSize().x*Config::HALF;
    // if(shape_.getPosition().x < halfWidth || 600-halfWidth <= shape_.getPosition().x)
    //     shape_.setPosition(prevposition);
    float mapsize = std::clamp(shape_.getPosition().x, halfWidth, Config::WIN_WIDTH-halfWidth);
    
    shape_.setPosition({mapsize, shape_.getPosition().y});
    
}

auto Paddle::GetGlobalBounds() const   ->sf::FloatRect
{
    return shape_.getGlobalBounds();
}