#include "Ball.h"
#include <cmath>
#include <numbers>
#include "Random.h"

Ball::Ball()
    :shape_     {Config::BALL_SIZE},
     speed_     {Config::BALL_SPEED*2.0}
{
    shape_.setFillColor({200, 200, 200, 255});
    shape_.setOrigin(shape_.getGeometricCenter());
    shape_.setPosition({Config:: WIN_WIDTH * Config::   HALF, 
                        Config::WIN_HEIGHT * Config::QUARTER});
    

    float angle = gRandom.GetFloat(Config::ZERO, 2 * std::numbers::pi_v<float>);
    direction_ = {std::cos(angle), std::sin(angle)};
}

void Ball::Draw(sf::RenderWindow& window_) const
{
    window_.draw(shape_);
}

void Ball::Move(float deltaTime)
{
    sf::Vector2f prevPosition = shape_.getPosition();

    shape_.move(deltaTime * speed_* direction_);

    if (shape_.getPosition().x <  shape_.getRadius() ||
        shape_.getPosition().x >= Config::WIN_WIDTH-shape_.getRadius())
    {
        shape_.setPosition(prevPosition);
        direction_.x *= Config::MINUS_ONE;
    }

    if(shape_.getPosition().y<shape_.getRadius())
    {
        shape_.setPosition(prevPosition);
        direction_.y *= Config::MINUS_ONE;
        shape_.setFillColor(sf::Color::Green);
    } 
    else shape_.setFillColor({200, 200, 200, 255});
}


auto Ball::GetGlobalBounds() const ->sf::FloatRect
{
    return shape_.getGlobalBounds();
}

auto Ball::GetDirection() const ->sf::Vector2f
{
    return direction_;
}

auto Ball::Bounce() -> void
{
    direction_.y *= Config::MINUS_ONE; 
}

auto Ball::IsOutside() const-> bool
{
    return (shape_.getPosition().y - shape_.getRadius())> Config::WIN_HEIGHT ;
}